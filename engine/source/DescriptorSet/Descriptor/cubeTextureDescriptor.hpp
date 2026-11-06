#ifndef CUBE_TEXTURE_DESCRIPTOR
#define CUBE_TEXTURE_DESCRIPTOR
#include<vulkan/vulkan.h>
#include<iostream>
#include<stdexcept>
#include<vector>

class cubeTextureDescriptor{
    public:

    cubeTextureDescriptor()=default;
    cubeTextureDescriptor(const cubeTextureDescriptor&)=delete;
    cubeTextureDescriptor& operator=(const cubeTextureDescriptor&)=delete;

    void createTextureDescriptor(VkDevice device,VkDescriptorSet& set,VkSampler sampler,std::vector<VkImageView>cubeTextures);
};
#endif