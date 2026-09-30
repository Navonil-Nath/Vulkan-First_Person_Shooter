#include"app.hpp"
#include<iostream>
#include<memory>
#include<GLFW/glfw3.h>
#include<string>

App::App(){
    m_vulkan_instance=std::make_unique<VulkanInstance>("Kitten_Engine");
    m_window_surface=std::make_unique<WindowSurface>(m_glfw_window.get(),m_vulkan_instance->get());
    m_physical_Device=std::make_unique<PhysicalDevice>(m_vulkan_instance->get(),m_window_surface->get());
}

App::~App(){
    
}


void App::Run(){
    //std::cout<<"engine initiated"<<std::endl;
    while(!m_glfw_window.ShouldCloseWindow()){
        m_glfw_window.pollEvents();
    }
}