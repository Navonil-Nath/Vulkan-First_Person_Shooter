/*

                                Theory
one importent concept that i have discussed before is that the VkImage or buffers that we create holds the information abotu the data stored and the location where it is sstored
it doesn't contain the actual memeory.The meomoryneeds to be assigned to those images and buffers seperatelly. To the images we assign the 
DEVICE_LOCAL_MEMORY and to the buffers we assign the memeory in the stagging bufferwhich can be ;ater transferred to the 
VRAM(DEVICE_LOCAL_MEMORY)

The Work of the FrameBuffer is to make Availbe to the gpu the VkImage color swapchain image and the VkImage Depth Image
 for rendering on a per frame basis

 The no of Framebuffers is equivalent to the no of Swapchain images so each image corrwsponds to a frambuffer containing the 
 swapchain image and a depthImage where in each frame operation after rendering into a color swapchain image the gpu releases
 the depth image to be filled by the gpu in the next frame operation and the color image gets locked until it;s contents are rendered
 to the screen this increases efficiency and makes theprocess faster 



*/

#ifndef FRAMEBUFFER_CLASS
#define FRAMEBUFFER_CLASS

#include<stdexcept>
#include<iostream>
#include<vulkan/vulkan.h>
#include<cstdlib>
#include<vector>
#include<array>

class FrameBuffer{
    public:
    FrameBuffer(VkDevice device,std::vector<VkImageView>swapColorImagesViews,VkImageView depthImageView,VkRenderPass renderpass,VkExtent2D extent);
    ~FrameBuffer();


    FrameBuffer(const FrameBuffer&)=delete;
    FrameBuffer& operator=(const FrameBuffer&)=delete;

    const std::vector<VkFramebuffer>& get() const{return m_framebuffer;}

    private:
    std::vector<VkFramebuffer> m_framebuffer;
    void CreateFrameBuffer(std::vector<VkImageView>swapColorImagesViews,VkImageView depthImageView,VkRenderPass renderpass,VkExtent2D extent);
    VkDevice m_device{VK_NULL_HANDLE};


};

#endif