#include"swapchain.hpp"
#include"swapchainSupport.hpp"
#include<algorithm>
#include<stdexcept>

Swapchain::Swapchain(VkDevice device,VkPhysicalDevice physicalDevice,VkSurfaceKHR surface,GLFWwindow* window):m_device(device),m_window(window){
    createSwapchain(physicalDevice,surface,window);
}

Swapchain::~Swapchain(){
    if(m_swapchain!=VK_NULL_HANDLE){
        vkDestroySwapchainKHR(m_device,m_swapchain,nullptr);
    }
}

void Swapchain::createSwapchain(VkPhysicalDevice physicalDevice,VkSurfaceKHR surface,GLFWwindow* window){
    SwapchainSupportDetails details=SwapchainSupport::querry(physicalDevice,surface);
    VkSurfaceFormatKHR imagFormat=chooseSwapImageFormat(details.format);
    VkPresentModeKHR imagePresentMode=chooseSwapImagePresentMode(details.presentMode);
    VkExtent2D imageExtent=chooseSwapImageExtent(details.capabilities,m_window);

    uint32_t imageCount=0;
    imageCount=details.capabilities.minImageCount+1;
    if(imageCount>details.capabilities.maxImageCount){
        imageCount=details.capabilities.maxImageCount;
    }
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface=surface;
    createInfo.minImageCount=imageCount;
    createInfo.imageFormat=imagFormat.format;
    createInfo.imageColorSpace=imagFormat.colorSpace;
    createInfo.imageExtent=imageExtent;
    createInfo.imageArrayLayers=1; //pls refer to the theory video before
    createInfo.imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
    createInfo.preTransform=details.capabilities.currentTransform;
    createInfo.presentMode=imagePresentMode;
    createInfo.clipped=VK_TRUE;

    if(vkCreateSwapchainKHR(m_device,&createInfo,nullptr,&m_swapchain)!=VK_SUCCESS){
        throw std::runtime_error("the swapchain coudn't be formed");
    }

    m_format=imagFormat.format;
    m_extent=imageExtent;


}  

VkSurfaceFormatKHR Swapchain::chooseSwapImageFormat(std::vector<VkSurfaceFormatKHR> formats){
    for(const auto& format:formats){
        if(format.format==VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace==VK_COLOR_SPACE_SRGB_NONLINEAR_KHR ){
            return format;
        }
    }
    return formats[0];
}

VkPresentModeKHR Swapchain::chooseSwapImagePresentMode(std::vector<VkPresentModeKHR>presentMode){

    for(const auto& mode:presentMode){
        if(mode==VK_PRESENT_MODE_MAILBOX_KHR){ //best as it enables triple buffering
            return mode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR; //default
}

VkExtent2D Swapchain::chooseSwapImageExtent(VkSurfaceCapabilitiesKHR capabilities,GLFWwindow* window){
    if(capabilities.currentExtent.width!=UINT32_MAX){
        return capabilities.currentExtent;
    }
    int width=0;
    int height=0;

    glfwGetFramebufferSize(window,&width,&height);
    VkExtent2D actualExtent={
        static_cast<uint32_t>(width),
        static_cast<uint32_t>(height)
        //there is no z componet for the color image as it is a 2d projected image
    };

    //now fix the upper and lower limit of the swap image extent it is very necessary
    actualExtent.width=std::clamp(actualExtent.width,capabilities.minImageExtent.width,capabilities.maxImageExtent.width);
    actualExtent.height=std::clamp(actualExtent.height,capabilities.minImageExtent.height,capabilities.maxImageExtent.height);

    return actualExtent;

}

