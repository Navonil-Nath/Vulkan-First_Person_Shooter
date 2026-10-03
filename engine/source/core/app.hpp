#ifndef APP_CLASS
#define APP_CLASS
#include<iostream>
#include<stdexcept>
#include"AppTestRunner.hpp"
#include"AppUi.hpp"
#include"glfw_window.hpp"
#include<memory>
#include"instance.hpp"
#include"window_surface.hpp"
#include"AppTestRunner.hpp"
#include"glfw_window.hpp"
#include"swapchainSupport.hpp"
#include"physicalDevice.hpp"
#include"logical_device.hpp"
#include"swapchain.hpp"
#include"swapchainImageView.hpp"
#include"depth_image.hpp"
#include"renderpass.hpp"
#include"framebuffer.hpp"
#include"command.hpp"
#include"sync.hpp"
#include"vertex.hpp"
#include"shaderModule.hpp"


class AppTestRunner;

class App{
    public:
    friend class AppTestRunner;
    int WIDTH=900;
    int HEIGHT=900;
    int MAX_FRAMES_IN_FLIGHT=3;
    App();
    ~App();

    App(const App&)=delete;
    App& operator=(const App&)=delete;

    

    void Run();
    private:
        Window m_glfw_window{WIDTH,HEIGHT,"fps Window"};
        std::unique_ptr<VulkanInstance>m_vulkan_instance;
        std::unique_ptr<WindowSurface>m_window_surface;
        std::unique_ptr<PhysicalDevice>m_physical_Device;
        std::unique_ptr<LogicalDevice>m_logical_device;
        std::unique_ptr<Swapchain>m_swapchain;
        std::unique_ptr<SwapchainImageView>m_swapchainImageView;
        std::unique_ptr<DepthResource>m_depthResource;
        std::unique_ptr<RenderPass>m_renderPass;
        std::unique_ptr<FrameBuffer>m_frambuffer_handle;
        std::unique_ptr<CommandBuffer>m_command_handle;
        std::unique_ptr<SyncObjects>m_sync_objects;
        
        
};

#endif