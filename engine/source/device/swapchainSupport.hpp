#ifndef SWAPCHAIN_SUPPORT
#define SWQPCHAON_SUPPORT
#include<vulkan/vulkan.h>
#include<vector>


struct SwapchainSupportDetails{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR>format;
    std::vector<VkPresentModeKHR>presentMode;

};

class SwapchainSupport{
    public:
        static SwapchainSupportDetails querry(VkPhysicalDevice device,VkSurfaceKHR surface);


};
#endif