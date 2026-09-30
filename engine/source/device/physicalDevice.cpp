#include"physicalDevice.hpp"
#include<stdexcept>
#include<vector>
#include"swapchainSupport.hpp"

PhysicalDevice::PhysicalDevice(VkInstance instance,VkSurfaceKHR surface){
    m_physical_Device=CreatePhysicalDevice(instance,surface);
    //print the name of the selected device
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(m_physical_Device,&properties);
    std::cout<<"the selected device is "<<properties.deviceName<<std::endl;
}



bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device,VkSurfaceKHR surface){
    auto details=SwapchainSupport::querry(device,surface);
    if(!details.format.empty() && !details.presentMode.empty()){
        return true;
    }
    else{
        return false;
    }
    
}
VkPhysicalDevice PhysicalDevice::CreatePhysicalDevice(VkInstance instance,VkSurfaceKHR surface){
    uint32_t deviceCount=0;
    VkPhysicalDevice selected_Device{VK_NULL_HANDLE};
    vkEnumeratePhysicalDevices(instance,&deviceCount,nullptr);
    if(deviceCount==0){
        throw std::runtime_error("Their is no gpus in this laptop");
    }
    std::vector<VkPhysicalDevice>all_devices(deviceCount);
    vkEnumeratePhysicalDevices(instance,&deviceCount,all_devices.data());

    for(const auto& device:all_devices){
        if(isDeviceSuitable(device,surface)){
            selected_Device=device;
            break;
        }
        continue;
    }
    

    if(selected_Device==VK_NULL_HANDLE){
        throw std::runtime_error("the laptop has no suitable gpu");
    }
    return selected_Device;
    
}
