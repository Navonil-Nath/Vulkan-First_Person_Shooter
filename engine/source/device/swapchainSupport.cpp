#include"swapchainSupport.hpp"




SwapchainSupportDetails SwapchainSupport::querry(VkPhysicalDevice device,VkSurfaceKHR surface){

    SwapchainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device,surface,&details.capabilities);
    uint32_t formatCount=0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device,surface,&formatCount,nullptr);

    if(formatCount!=0){
        details.format.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device,surface,&formatCount,details.format.data());
    }   

    uint32_t presentModeCount=0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device,surface,&presentModeCount,nullptr);

    if(presentModeCount!=0){
        details.presentMode.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device,surface,&presentModeCount,details.presentMode.data());
    }

    return details;
}