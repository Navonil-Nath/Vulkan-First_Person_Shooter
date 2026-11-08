#ifndef CREATE_IMAGE_VIEWS_AND_IMAGES
#define CREATE_IMAGE_VIEWS_AND_IMAGES
#include<vulkan/vulkan.hpp>
#include<stdexcept>
#include"command.hpp"
#include"TextureImages.hpp"

class CreateImage{
    public:
    CreateImage()=default;
    
    CreateImage(const CreateImage&)=delete;
    CreateImage& operator=(const CreateImage&)=delete;

    void UploadFromBuffer(VkImage image,CommandBuffer& bufferHandle,VkQueue queue,VkBuffer staggingBuffer,Texture_Image& image_Object);

    private:
     
    void copyBufferData(VkImage image,CommandBuffer& bufferHandle,VkQueue queue,VkBuffer staggingBuffer,Texture_Image& image_Object);
    void TransitionLayout(VkImage image,CommandBuffer& bufferHandle,VkQueue queue,VkImageLayout oldLayout,VkImageLayout newLayout);
};

#endif