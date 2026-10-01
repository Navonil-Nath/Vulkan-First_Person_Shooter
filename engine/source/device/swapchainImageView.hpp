#ifndef VULKAN_SWAPCHAIN_IMAGES
#define VULKAN_SWAPCHAIN_IMAGES

#include"swapchain.hpp"
#include<iostream>
#include<stdexcept>
#include<vector>
#include<vulkan/vulkan.h>

class SwapchainImageView{
    public:
    SwapchainImageView(VkDevice device,VkSwapchainKHR swapchain,VkFormat format);
    ~SwapchainImageView();

    SwapchainImageView(const SwapchainImageView&)=delete;
    SwapchainImageView& operator=(const SwapchainImageView&)=delete;

    const std::vector<VkImageView> get() const {return m_imageViews;}

    private:
    VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
    VkFormat m_format;
    VkDevice m_device{VK_NULL_HANDLE};
    std::vector<VkImage>m_images;
    std::vector<VkImageView>m_imageViews;

    void RetrieveSwapImages();
    void CreateSwapImgViews();
};

#endif