#include"TextureImages.hpp"
#include<stdexcept>

Texture_Image::Texture_Image(VkDevice device,VkPhysicalDevice physical_device,uint32_t height,uint32_t width,VkFormat format):m_device(device),m_format(format),m_texture_width(width),m_texture_height(height),m_physical_device(physical_device){

    CreateImage(m_physical_device);
    CreateImageViews();

}

Texture_Image::~Texture_Image(){
    if(m_image_view!=VK_NULL_HANDLE){
        vkDestroyImageView(m_device,m_image_view,nullptr);
    }
    if(m_image!=VK_NULL_HANDLE){
        vkDestroyImage(m_device,m_image,nullptr);
    }
    if(m_device_memory!=VK_NULL_HANDLE){
        vkFreeMemory(m_device,m_device_memory,nullptr);
    }
}

void Texture_Image::CreateImage(VkPhysicalDevice physical_device){
    VkImageCreateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    createInfo.imageType=VK_IMAGE_TYPE_2D;
    createInfo.extent.width=m_texture_width;
    createInfo.extent.height=m_texture_height;
    createInfo.extent.depth=1;
    createInfo.mipLevels=1;
    createInfo.arrayLayers=1;
    createInfo.format=m_format;
    createInfo.tiling=VK_IMAGE_TILING_OPTIMAL;
    createInfo.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    createInfo.usage=VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    createInfo.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
    createInfo.samples=VK_SAMPLE_COUNT_1_BIT;
    
    //the image will still not be pointing to any memeory block on gpu
    if(vkCreateImage(m_device,&createInfo,nullptr,&m_image)!=VK_SUCCESS){
        throw std::runtime_error("the image cannot be formed");
    }

    //now we will need to allocate memeory on the gpu which can hold on to contents as described in the 
    //vk_image's extent
    //getting the memeory requirements
    VkMemoryRequirements memrequirements{};
    vkGetImageMemoryRequirements(m_device,m_image,&memrequirements);
    
    //allocate the memeory which meets the memrequirements
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize=memrequirements.size;
    allocInfo.memoryTypeIndex=findMemeoryType(m_physical_device,memrequirements.memoryTypeBits,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if(vkAllocateMemory(m_device,&allocInfo,nullptr,&m_device_memory)!=VK_SUCCESS){
        throw std::runtime_error("the memeory for the texture cannot be allocated");
    }

    //if allocation successfull allocate the memeory pointer to the vkimage
    vkBindImageMemory(m_device,m_image,m_device_memory,0);

}

void Texture_Image::CreateImageViews(){
        VkImageViewCreateInfo createInfo{};
        createInfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image=m_image;
        createInfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format=m_format;
        createInfo.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel=0;
        createInfo.subresourceRange.levelCount=1;
        createInfo.subresourceRange.baseArrayLayer=0;
        createInfo.subresourceRange.layerCount=1;

        if(vkCreateImageView(m_device,&createInfo,nullptr,&m_image_view)!=VK_SUCCESS){
            throw std::runtime_error("the image view of the image cannot be formed");
        }


}

uint32_t Texture_Image::findMemeoryType(VkPhysicalDevice device,uint32_t typeFilter,VkMemoryPropertyFlags flags){
    VkPhysicalDeviceMemoryProperties allproperties{};
    vkGetPhysicalDeviceMemoryProperties(m_physical_device,&allproperties);
    
    //finding the suitable memeory out of all the availabel options

    for(uint32_t i=0;i<allproperties.memoryTypeCount;++i){
        bool typeMatch=(typeFilter & (1<<i))!=0;
        bool propertyMatch=(allproperties.memoryTypes[i].propertyFlags & flags)==flags;

        if(typeMatch && propertyMatch){
            return i;
        }
    }
}
