#ifndef TEXTURE_IMAGE_CLASS
#define TEXTURE_IMAGE_CLASS

#include<vulkan/vulkan.hpp>
#include<stdexcept>
#include"command.hpp"

class Texture_Image{
    public:
    friend class CreateImage;
    Texture_Image(VkDevice device,VkPhysicalDevice physical_device,uint32_t height,uint32_t widht,VkFormat format);
    //format == VK_FORMAT_R8G8B8A8_SRGB for albedo images and VK_FORMAT_R8G8_UNIFORM for the normal and roughness images
    ~Texture_Image();

    Texture_Image(const Texture_Image&)=delete;
    Texture_Image& operator=(const Texture_Image&)=delete;

    VkImage get_image(){return m_image;}
    VkImageView get_image_view(){return m_image_view;}

    private:

    void CreateImage(VkPhysicalDevice device);
    void CreateImageViews();
    uint32_t findMemeoryType(VkPhysicalDevice device,uint32_t typeFilter,VkMemoryPropertyFlags flags);
    
    VkDevice m_device{VK_NULL_HANDLE};
    VkPhysicalDevice m_physical_device{VK_NULL_HANDLE};
    VkImage m_image{VK_NULL_HANDLE};
    VkImageView m_image_view{VK_NULL_HANDLE};
    VkDeviceMemory m_device_memory{VK_NULL_HANDLE};
    uint32_t m_texture_width{0};
    uint32_t m_texture_height{0};
    VkFormat m_format; 

};



#endif

/*
                                                Theory
after uploading the texture image to the cpu heap using the imageLoader function and then to the stagging buffer using the stagging buffer function
we then use this class "Texture_Image" to upload each image to the vram
the class upon initating the forms and allocates a memeory block acccording to the height and width we give it 
on the gpu vram  and binds it with the VkImage andforms the VkImage view
but the image is still ponting to an empty memeory block
here then we call the UploadFromBuffer function which first changes the vkimage's layout from undefined to transition then 
we call the copybuffer function which copies the 1d buffer data from the stagging buffer to an 2d memeory block
then again call the TransitionLayout function which then transforms the layout of the image to read only for the shaders

*/