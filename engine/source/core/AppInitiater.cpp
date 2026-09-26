#include"app.cpp"


//i am doing this beacuse the App constructor might get huge in the future
App::App(){
    obj_vulkan_instance=std::make_unique<VulkanInstance>();
    obj_window_surface=std::make_unique<WindowSurface>();

}

App::~App(){

}