#ifndef PHYSICAL_DEVICE
#define PHYSICAL_DEVICE

#include<vulkan/vulkan.h>
#include<iostream>

class PhysicalDevice{
    public:
    PhysicalDevice(VkInstance instance,VkSurfaceKHR surface);
    ~PhysicalDevice();

    PhysicalDevice(const PhysicalDevice&)=delete;
    PhysicalDevice& operator=(const PhysicalDevice&)=delete;

    VkPhysicalDevice get(){return m_physical_Device;}

    private:
    
    VkPhysicalDevice CreatePhysicalDevice(VkInstance instance,VkSurfaceKHR surface);
    VkPhysicalDevice m_physical_Device{VK_NULL_HANDLE};

    bool isDeviceSuitable(VkPhysicalDevice device,VkSurfaceKHR surface);

};

#endif