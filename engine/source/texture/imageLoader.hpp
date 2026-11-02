#ifndef IMAGE_LOADER_CLASS
#define IMAGE_LOADER_CLASS
#include "stb_image.hpp"
#include<stdexcept>
#include<string>

struct LoadedImage{
    //this shall contain a normal .png image

    int width{0};
    int height{0};
    int channels{0};
    stbi_uc* pixels=nullptr;

    LoadedImage()=default;

    ~LoadedImage();

    //delete the copy constructors and assignemt
    LoadedImage(const LoadedImage&)=delete;
    LoadedImage& operator=(const LoadedImage&)=delete;

    //enabling the move constructirs

    LoadedImage(LoadedImage&& other)noexcept;
    LoadedImage& operator=(LoadedImage&& other)noexcept;


};

struct LoadedSkyBoxImage{
    //this shall hold the cubemapImage

    int width{0};
    int height{0};
    int channels{0};
    float* pixels_skybox{nullptr};

    LoadedSkyBoxImage()=default;
    ~LoadedSkyBoxImage();

    //deleting the copy operators
    LoadedSkyBoxImage(const LoadedSkyBoxImage&)=delete;
    LoadedSkyBoxImage& operator=(const LoadedSkyBoxImage&)=delete;

    //enable the move operators
    LoadedSkyBoxImage(LoadedSkyBoxImage&& other)noexcept;
    LoadedSkyBoxImage& operator=(LoadedSkyBoxImage&& other)noexcept;


    
};

class ImageLoader{
    static LoadedImage loadTexture(std::string path);  

    static LoadedSkyBoxImage loadSkyboxTexture(std::string path);
};

#endif