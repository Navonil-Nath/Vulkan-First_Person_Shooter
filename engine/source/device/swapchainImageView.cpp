#include"swapchainImageView.hpp"

SwapchainImageView::SwapchainImageView(VkDevice device,VkSwapchainKHR swapchain,VkFormat format):m_device(device),m_format(format),m_swapchain(swapchain){

    RetrieveSwapImages();
    CreateSwapImgViews();
}


SwapchainImageView::~SwapchainImageView(){
    for(auto& imageView:m_imageViews){
        if(imageView!=VK_NULL_HANDLE){
            vkDestroyImageView(m_device,imageView,nullptr);
        }
    }

}

void SwapchainImageView::RetrieveSwapImages(){

    uint32_t imageCount=0;
    vkGetSwapchainImagesKHR(m_device,m_swapchain,&imageCount,nullptr);
    m_images.resize(imageCount);
    vkGetSwapchainImagesKHR(m_device,m_swapchain,&imageCount,m_images.data());

}
void SwapchainImageView::CreateSwapImgViews(){
    m_imageViews.resize(m_images.size());
    for(size_t i=0;i<m_imageViews.size();++i){
        VkImageViewCreateInfo createInfo{};
        createInfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image=m_images[i];
        createInfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format=m_format;
        createInfo.components={  //default setting
            VK_COMPONENT_SWIZZLE_IDENTITY, //R
            VK_COMPONENT_SWIZZLE_IDENTITY, //G
            VK_COMPONENT_SWIZZLE_IDENTITY, //B
            VK_COMPONENT_SWIZZLE_IDENTITY //A
        };
        createInfo.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT; //all the swapchain images to be color images
        createInfo.subresourceRange.baseMipLevel=0; //default sharp image
        createInfo.subresourceRange.levelCount=1;
        createInfo.subresourceRange.layerCount=1;

        if(vkCreateImageView(m_device,&createInfo,nullptr,&m_imageViews[i])!=VK_SUCCESS){
            throw std::runtime_error("a image view cudn't be formed");
        }   
    }


}

