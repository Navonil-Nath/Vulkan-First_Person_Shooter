#ifndef VULKAN_INSTANCE_CLASS
#define VULKAN_INSTANCE_CLASS

#include<vulkan/vulkan.h>


class VulkanInstance{
    public: 
        VulkanInstance();
        ~VulkanInstance();

        VulkanInstance(const VulkanInstance&)=delete;
        VulkanInstance& operator=(const VulkanInstance&)=delete;
        VkInstance get(){m_instance;}
        
    private:

        VkInstance m_instance=VK_NULL_HANDLE;

};

#endif