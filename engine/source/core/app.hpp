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

class App{
    public:
    int WIDTH=900;
    int HEIGHT=900;
    int MAX_FRAMES_IN_FLIGHT=1;
    App();
    ~App();

    App(const App&)=delete;
    App& operator=(const App&)=delete;

    void Run();
    private:
        Window m_glfw_window{WIDTH,HEIGHT,"fps Window"};
        std::unique_ptr<VulkanInstance>obj_vulkan_instance;
        std::unique_ptr<WindowSurface>obj_window_surface;
        
};

#endif