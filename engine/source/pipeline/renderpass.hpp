/*
                                THEORY
Renderpass is what initiates a graphics pipeline

1.Before the gpu can render into the image<raw memeory> of the framebuffer or swapchainor the cpu can start writting into the 
command buffers.thee renderpass defines defines the gpu what images are available for it to use ,their format and extent
in our ccase it is color and depth ie VK_IMAGE_ASPECT_COLOR_BIT and VK_IMAGE_ASPECT_DEPTH_BIT

2.and tells the gpu what to do with the images before and after rendering ie whether to keep the prev rendered data and write on the new existing layers or 
clean all the layers and start fresh each frame!!

3. it also tells the gpu whether to start off-screen or on-screen rendering


*/

#ifndef RENDERPASS_CLASS
#define RENDERPASS_CLASS
#include<iostream>
#include<stdexcept>
#include<vulkan/vulkan.h>


class RenderPass{
    public:
        RenderPass(VkFormat colorFormat,VkFormat depthFormat,VkDevice device);
        ~RenderPass();

        RenderPass(const RenderPass&)=delete;
        RenderPass& operator=(const RenderPass&)=delete;
        VkRenderPass get()const {return m_renderPass;}


    private:
        VkRenderPass m_renderPass{VK_NULL_HANDLE};
        void CreateRenderPass(VkFormat colorFormat,VkFormat depthFormat);

        VkDevice m_device{VK_NULL_HANDLE};
  
};


#endif