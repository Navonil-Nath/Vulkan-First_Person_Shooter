#include"app.hpp"
#include<iostream>
App::App(){
    std::cout<<"i like sexy bitches"<<std::endl;
    std::cout<<"app class initiated"<<std::endl;
}

App::~App(){
    std::cout<<"App class destroyed"<<std::endl;
}

void App::Run(){
    std::cout<<"engine initiated"<<std::endl;
}