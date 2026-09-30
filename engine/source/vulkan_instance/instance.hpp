#ifndef VULKAN_INSTANCE_CLASS
#define VULKAN_INSTANCE_CLASS

#include<vulkan/vulkan.h>
#include<iostream>
#include<cstdlib>
#include<stdexcept>
#include<GLFW/glfw3.h>
#include<string>
#include<vector>


class VulkanInstance{
    public: 
        VulkanInstance(const std::string& appName);
        ~VulkanInstance();

        VulkanInstance(const VulkanInstance&)=delete;
        VulkanInstance& operator=(const VulkanInstance&)=delete;

        VkInstance get(){return m_instance;}
        
    private:

        VkInstance m_instance=VK_NULL_HANDLE;
        void CreateInstance(const std::string& appName);
        void setUpDebugMessenger();
        bool checkValidationLayerSupport();
        std::vector<const char*> glfwExtensions();
        VkDebugUtilsMessengerEXT m_debugMessenger{VK_NULL_HANDLE};
        std::vector<const char*> getRequiredGlfwExtensions();
        


};

#endif