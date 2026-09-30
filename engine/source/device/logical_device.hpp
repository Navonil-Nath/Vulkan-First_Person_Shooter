/*
today we will start by creating the logical devie
1.first we will queerry the physical devoce for a queufamilly that supports both graphics commands and surface commands
2.enable VK_KHR_swpachain this enables rendering to the screenm or window surface
3.enable gpu features like samplerAnisotophy which will enable us to obtain clear and sharp images of the textures even in steep angles
4.retrive handles to the VkQueue from the selected physical device
5. for now only one VkQueue ,thisis where we wil submit all our command buffers
6.enabling check in ~App to ensure that the resources are properlly deallocated before logical device goes out of scope

*/

#ifndef LOGICAL_DEVICE_IMPL
#define LOGICAL_DEVICE_IMPL

#include<cstdlib>
#include<iostream>
#include<vulkan/vulkan.h>
class LogicalDevice{
    public:

    LogicalDevice(VkPhysicalDevice device,VkSurfaceKHR surface);
    ~LogicalDevice();

    LogicalDevice(const LogicalDevice&)=delete;
    LogicalDevice& operator=(const LogicalDevice&)=delete;

    VkQueue getQueue(){return m_queueHandle;}
    VkDevice get(){return m_device;}

    uint32_t getQueueIndex(){return m_QueueIndex;}
    private:

    VkDevice m_device{VK_NULL_HANDLE};
    VkQueue m_queueHandle{VK_NULL_HANDLE};
    uint32_t m_QueueIndex{0};
    bool isQueuePresent=false; //true if a queufamilly contains both graphics and present queue

    void CreateDevice(VkPhysicalDevice device);
    void findQueueFamilly(VkPhysicalDevice device,VkSurfaceKHR surface);
};
#endif