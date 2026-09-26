#ifndef VULKAN_SURFACE_CLASS
#define VULKAN_SURFACE_CLASS
#include<stdexcept>
#include "window_surface.hpp"

WindowSurface::WindowSurface(GLFWwindow* window,VkInstance instance):m_instance(instance){
    if(glfwCreateWindowSurface(instance,window,nullptr,&m_surface)!=VK_SUCCESS){
        throw std::runtime_error("the window surface cannot be formed");
    }
}

WindowSurface::~WindowSurface(){
    if(m_surface!=VK_NULL_HANDLE){
        vkDestroySurfaceKHR(m_instance,m_surface,nullptr);
    }
}

#endif