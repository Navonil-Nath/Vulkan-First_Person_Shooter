#include"imageLoader.hpp"

LoadedImage::~LoadedImage(){
    if(pixels!=nullptr){
        stbi_image_free(pixels);
    }
}
LoadedSkyBoxImage::~LoadedSkyBoxImage(){
    if(pixels_skybox!=nullptr){
        stbi_image_free(pixels_skybox);
    }
}

LoadedImage ImageLoader::loadTexture(std::string path){
    LoadedImage image{};
    image.pixels=stbi_load(path.c_str(),&image.width,&image.height,&image.channels,STBI_rgb_alpha); //STBI_rgb_aplha means 4 channels
    if(image.pixels==nullptr || image.width<=0 || image.height<=0){
        throw std::runtime_error("the texture cannot be loaded in the path :"+ path);
    }
    image.channels=4;
    return image;
}

LoadedSkyBoxImage ImageLoader::loadSkyboxTexture(std::string path){
    LoadedSkyBoxImage image{};
    image.pixels_skybox=stbi_loadf(path.c_str(),&image.width,&image.height,&image.channels,STBI_rgb_alpha);
    if(image.pixels_skybox==nullptr || image.width<=0 || image.height<=0){
        throw std::runtime_error("the texture cannot be loaded from the path :"+ path);
    }
    image.channels=4;
    return image;
}

//describing the move sementics

LoadedImage::LoadedImage(LoadedImage&& other)noexcept:width(other.width),height(other.height),channels(other.channels),pixels(other.pixels){


    other.width=0;
    other.height=0;
    other.channels=0;
    other.pixels=nullptr;

    
}

//describing the move assignment operator

LoadedImage& LoadedImage::operator=(LoadedImage&& other)noexcept{
    if(this!=&other){
        if(pixels!=nullptr){
            stbi_image_free(pixels);
        }
        width=other.width;
        height=other.height;
        channels=other.channels;
        pixels=other.pixels;

        other.width=0;
        other.height=0;
        other.channels=0;
        other.pixels=nullptr;
    }
    return *this;

}

//for the skybox image loader

LoadedSkyBoxImage::LoadedSkyBoxImage(LoadedSkyBoxImage&& other)noexcept:width(other.width),height(other.height),channels(other.channels),pixels_skybox(other.pixels_skybox){

    other.width=0;
    other.height=0;
    other.channels=0;
    other.pixels_skybox=nullptr;

}

LoadedSkyBoxImage& LoadedSkyBoxImage::operator=(LoadedSkyBoxImage&& other)noexcept{
    if(this!=&other){
        if(pixels_skybox!=nullptr){
            stbi_image_free(pixels_skybox);
        }
        width=other.width;
        height=other.height;
        channels=other.channels;
        pixels_skybox=other.pixels_skybox;

        other.width=0;
        other.height=0;
        other.channels=0;
        other.pixels_skybox=nullptr;
    }
    return *this;
}


