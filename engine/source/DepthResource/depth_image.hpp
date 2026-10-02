/*
                                  Theory
The 3D objects that we see in the screen must be converted to 2D space beacuse our laptop screen is 2D \
the 2d transformation is done w.r.t to the camera or view matrix with the help of the projection matrix
the projection matirx adds depth to the scene.the gpu then caculates specific depth value of each pixel in the scene and
saves them in the depth buffer.the depth buffer consists of a buffer which configuration of the hardware memeory,a VkImage and 
its VkImageView .The VkImage is in the device local memeory or the gpu memory.

!!//here we kept the extent and format of the depth image same as that of the swapchain images only the image type chaged for
      storing depth value of each pixels<--(imp)
*/
#ifndef VK_DEPTH_IMAGE
#define VK_DEPTH_IMAGE
#include"vulkan/vulkan.h"
#include<cstdlib>
#include<stdexcept>
#include"swapchainSupport.hpp"

class DepthResource{
    public:
        DepthResource(VkPhysicalDevice physical_Device,VkDevice device,VkExtent2D extent,VkFormat format);
        ~DepthResource();

        DepthResource(const DepthResource&)=delete;
        DepthResource& operator=(const DepthResource&)=delete;

        VkImageView getImageView()const{return m_depthImageView;}
        VkImage getImage(){return m_depthImage;}
        VkFormat getFormat(){return m_depthImageFormat;}

    private:
        VkImage m_depthImage{VK_NULL_HANDLE};
        VkImageView m_depthImageView{VK_NULL_HANDLE};

        uint32_t findMemoryType(VkPhysicalDevice device,uint32_t memoryFilter,VkMemoryPropertyFlags properties)const;
        void CreateDepthImage(VkExtent2D extent,VkFormat format);
        void CreateDepthImageView();

        VkDeviceMemory m_GpuMemory{VK_NULL_HANDLE};
        VkFormat m_depthImageFormat;

        VkDevice m_Device{VK_NULL_HANDLE};
        VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
        void getDeviceMemory();

};
#endif