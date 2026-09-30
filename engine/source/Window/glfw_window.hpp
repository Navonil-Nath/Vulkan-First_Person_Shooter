#ifndef GLFW_WINDOW_CLASS
#define GLFW_WINDOW_CLASS
#include<iostream>
#include<GLFW/glfw3.h>
#include<stdexcept>
#include<string>

class Window{
    public:
        Window(int width,int height,const std::string title);
        ~Window();

        Window(const Window&)=delete;
        Window& operator=(const Window&)=delete;

        void pollEvents();

        bool ShouldCloseWindow();
        GLFWwindow* get()const {return m_window;}

        void setCursorMode(int mode);
        int getCursorMode();

    private:

        GLFWwindow* m_window=nullptr;
        int m_width=0;
        int m_height=0;
        std::string m_string;

        void InitWindow();

};

#endif