#include"depth_image.hpp"
#include<stdexcept>

DepthResource::DepthResource(VkPhysicalDevice physical_Device,VkDevice device,VkExtent2D extent,VkFormat format):m_Device(device),m_physicalDevice(physical_Device),m_depthImageFormat(format){
    CreateDepthImage(extent,format);
    CreateDepthImageView();
}
DepthResource::~DepthResource(){
    if(m_depthImageView!=VK_NULL_HANDLE){
        vkDestroyImageView(m_Device,m_depthImageView,nullptr);
    }
    if(m_depthImage!=VK_NULL_HANDLE){
        vkDestroyImage(m_Device,m_depthImage,nullptr);

    }
    if(m_GpuMemory!=VK_NULL_HANDLE){
        vkFreeMemory(m_Device,m_GpuMemory,nullptr);
    }
}

uint32_t DepthResource::findMemoryType(VkPhysicalDevice device,uint32_t typeFilter,VkMemoryPropertyFlags properties)const {
    VkPhysicalDeviceMemoryProperties memoryProp{};
    vkGetPhysicalDeviceMemoryProperties(device,&memoryProp);
    
    //the typeFilter is a bit mask 
    for(uint32_t i=0;i<memoryProp.memoryTypeCount;++i){
        bool istypeMatch=typeFilter & (1<<i);
        //watch if the patticular memeory type has the required properties as required by you
        bool ispropMatch=(memoryProp.memoryTypes[i].propertyFlags & properties)==properties;
        if(istypeMatch && ispropMatch){
            return i;
        }

    }
    throw std::runtime_error("the reuired properties for depth image coudn't be sufficed by any of the available memeory types in the selected gpu");
}


void DepthResource::CreateDepthImage(VkExtent2D extent,VkFormat format){
//here we kept the extent and format of the depth image same as that of the swapchain images only the image type chaged for storing depth value of each pixels
    VkImageCreateInfo imageInfo{};
    imageInfo.sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType=VK_IMAGE_TYPE_2D;
    imageInfo.extent={extent.width,extent.height,1};
    imageInfo.mipLevels=1;
    imageInfo.arrayLayers=1;
    imageInfo.format=format;
    imageInfo.tiling=VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage=VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    imageInfo.samples=VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
    

    if(vkCreateImage(m_Device,&imageInfo,nullptr,&m_depthImage)!=VK_SUCCESS){
        throw std::runtime_error("the depth image coudn't be formed");
    }
    
    getDeviceMemory();

}

void DepthResource::getDeviceMemory(){
    VkMemoryRequirements requirements{};
    vkGetImageMemoryRequirements(m_Device,m_depthImage,&requirements);


    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.memoryTypeIndex=findMemoryType(m_physicalDevice,requirements.memoryTypeBits,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);


    if(vkAllocateMemory(m_Device,&allocateInfo,nullptr,&m_GpuMemory)!=VK_SUCCESS){
        throw std::runtime_error("unable to assign the memory in the gpu local area");
    }

    //now bond the assigned gpu  memory to the formed image
    vkBindImageMemory(m_Device,m_depthImage,m_GpuMemory,0);


}


void DepthResource::CreateDepthImageView(){

    //now that the image has been formed and assigned space in the local gpu area
    //ie the VRAM <fatest one for gpu operations>
    //its time to form the image views ie with which we will work in out application
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image=m_depthImage;
    viewInfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format=m_depthImageFormat;
    viewInfo.subresourceRange.aspectMask=VK_IMAGE_ASPECT_DEPTH_BIT;
    viewInfo.subresourceRange.baseMipLevel=0;
    viewInfo.subresourceRange.levelCount=1;
    viewInfo.subresourceRange.baseArrayLayer=0;
    viewInfo.subresourceRange.layerCount=1;

    if(vkCreateImageView(m_Device,&viewInfo,nullptr,&m_depthImageView)!=VK_SUCCESS){
        throw std::runtime_error("the image view coudn't be created");
    }
    


}