#ifndef APP_CLASS
#define APP_CLASS
#include<iostream>
#include<stdexcept>
#include"AppTestRunner.hpp"
#include"AppUi.hpp"
#include"glfw_window.hpp"

class App{
    public:
    App();
    ~App();

    void Run();
    private:
        Window m_window;

};

#endif