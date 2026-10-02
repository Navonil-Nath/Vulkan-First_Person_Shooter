#include"app.hpp"
#include<iostream>
#include<memory>
#include<GLFW/glfw3.h>
#include<string>

App::App(){
    m_vulkan_instance=std::make_unique<VulkanInstance>("Kitten_Engine");
    m_window_surface=std::make_unique<WindowSurface>(m_glfw_window.get(),m_vulkan_instance->get());
    m_physical_Device=std::make_unique<PhysicalDevice>(m_vulkan_instance->get(),m_window_surface->get());
    m_logical_device=std::make_unique<LogicalDevice>(m_physical_Device->get(),m_window_surface->get());
    m_swapchain=std::make_unique<Swapchain>(m_logical_device->get(),m_physical_Device->get(),m_window_surface->get(),m_glfw_window.get());
    m_swapchainImageView=std::make_unique<SwapchainImageView>(m_logical_device->get(),m_swapchain->get(),m_swapchain->getFormat());
    m_depthResource=std::make_unique<DepthResource>(m_physical_Device->get(),m_logical_device->get(),m_swapchain->getExtent(),VK_FORMAT_D32_SFLOAT);
    //m_depthResource contains the both view and image
}

App::~App(){
    if(m_logical_device){
        vkDeviceWaitIdle(m_logical_device->get()); //wait for other resources to finsih deallocation before deallocating the logical device
    }
    
}


void App::Run(){
    //std::cout<<"engine initiated"<<std::endl;
    while(!m_glfw_window.ShouldCloseWindow()){
        m_glfw_window.pollEvents();
    }
}