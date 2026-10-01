#ifndef SWAPCHAIN_CLASS
#define SWAPCHAIN_CLASS
#include<GLFW/glfw3.h>
#include<iostream>
#include<vulkan.h>
#include<vector>
class Swapchain{
    public:
        Swapchain(VkDevice device,VkPhysicalDevice physicalDevice,VkSurfaceKHR surface,GLFWwindow* window);
        ~Swapchain();

        Swapchain(const Swapchain&)=delete;
        Swapchain& operator=(const Swapchain&)=delete;

        VkSwapchainKHR get(){return m_swapchain;}
        VkFormat getFormat(){return m_format;}
        VkExtent2D getExtent(){return m_extent;}


    private:
        VkDevice m_device{VK_NULL_HANDLE};
        VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
        VkFormat m_format;
        VkExtent2D m_extent;
        GLFWwindow* m_window=nullptr;

        void createSwapchain(VkPhysicalDevice physicalDevice,VkSurfaceKHR surface,GLFWwindow* window);
        VkExtent2D chooseSwapImageExtent(VkSurfaceCapabilitiesKHR capabilities,GLFWwindow* window);
        VkPresentModeKHR chooseSwapImagePresentMode(const std::vector<VkPresentModeKHR>availabbleModes);
        VkSurfaceFormatKHR chooseSwapImageFormat(const std::vector<VkSurfaceFormatKHR> availableFormats);


};
#endif