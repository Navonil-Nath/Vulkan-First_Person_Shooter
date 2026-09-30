#include"logical_device.hpp"
#include<vector>
#include<stdexcept>

namespace {
    const std::vector<const char*>deviceExtensions={
        "VK_KHR_SWAPCHAIN_EXTENSION_NAME"
    };
}

LogicalDevice::LogicalDevice(VkPhysicalDevice device,VkSurfaceKHR surface){
    findQueueFamilly(device,surface);
    CreateDevice(device);

}

LogicalDevice::~LogicalDevice(){
    if(m_device!=VK_NULL_HANDLE){
        vkDestroyDevice(m_device,nullptr);
    }
}

void LogicalDevice::CreateDevice(VkPhysicalDevice device){
    float queuePriority=1.0f;
    //here we will select only one queue fron the queu family
    VkDeviceQueueCreateInfo queueInfo{};
    queueInfo.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex=m_QueueIndex;
    queueInfo.queueCount=1;
    queueInfo.pQueuePriorities=&queuePriority;
     //enabling sampler Anisotrophy

    VkPhysicalDeviceFeatures device_features{};
    device_features.samplerAnisotropy=VK_TRUE;


    VkDeviceCreateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos=&queueInfo;
    createInfo.queueCreateInfoCount=1;
    createInfo.pEnabledFeatures=&device_features;
    createInfo.enabledExtensionCount=static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames=deviceExtensions.data();

    if(vkCreateDevice(device,&createInfo,nullptr,&m_device)!=VK_SUCCESS){
        throw std::runtime_error("unable to create logical device");
    }

    vkGetDeviceQueue(m_device,m_QueueIndex,0,&m_queueHandle); //the return type of the vkgetDeviceQueue is void

    if(m_queueHandle==nullptr){
        throw std::runtime_error("the queue handle coudn't be formed");
    }

}

void LogicalDevice::findQueueFamilly(VkPhysicalDevice device,VkSurfaceKHR surface){
    uint32_t queueFamilyCount=0;
    vkGetPhysicalDeviceQueueFamilyProperties(device,&queueFamilyCount,nullptr);

    if(queueFamilyCount==0){
        throw std::runtime_error("falled to get the queue families");
    }
    std::vector<VkQueueFamilyProperties> all_queues(queueFamilyCount);

    vkGetPhysicalDeviceQueueFamilyProperties(device,&queueFamilyCount,all_queues.data());

    //now search for the queue family that supports the graphics operations and presentation operations
    for(uint32_t i=0;i<queueFamilyCount;++i){
        VkBool32 presentSupport=false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device,i,surface,&presentSupport);
        //presenSupport will be true if it supports
        if(presentSupport==true){
            if(all_queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
                m_QueueIndex=i;
                isQueuePresent=true;
                break;
            }
        } 
        else{
            continue;
        }
    }
    if(isQueuePresent==false){
        throw std::runtime_error("no supported queues are present");
    }

}