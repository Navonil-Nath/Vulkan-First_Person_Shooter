#ifndef WINDOW_SURFACE_CLASS
#define WINDOW_SURFACE_CLASS

#include<vulkan/vulkan.h>
#include<GLFW/glfw3.h>

class WindowSurface{
    public:
        WindowSurface(GLFWwindow* window,VkInstance instance);
        ~WindowSurface();

        WindowSurface(const WindowSurface&)=delete;
        WindowSurface& operator=(const WindowSurface&)=delete;

        VkSurfaceKHR get(){return m_surface;}

    private:
        
        VkSurfaceKHR m_surface=VK_NULL_HANDLE;
        VkInstance m_instance=VK_NULL_HANDLE;
};      


#endif