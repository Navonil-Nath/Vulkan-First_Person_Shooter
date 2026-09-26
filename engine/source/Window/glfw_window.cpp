#include"glfw_window.hpp"

Window::Window(int width,int height,const std::string& title):m_width(width),m_height(height),m_string(title){
    InitWindow();
}

void Window::InitWindow(){
    if(!glfwInit()){
        throw std::runtime_error("the glfw library coudn't be initiated");
    }
    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);

    m_window=glfwCreateWindow(m_width,m_height,m_string.c_str(),nullptr,nullptr);
    if(m_window=nullptr){
        std::cout<<"the window coudn't be created"<<std::endl;
        glfwTerminate();
    }

}

Window::~Window(){
    if(m_window){
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}   

bool Window::ShouldCloseWindow(){
    return glfwWindowShouldClose(m_window);
}

void Window::pollEvents(){
    return glfwPollEvents();
}

