#include<iostream>
#include<stdexcept>
#include"app.hpp"


int main(){
    try{
        App app;
        app.Run();
    }
    catch(std::exception& e){
        std::cerr<<e.what()<<std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}