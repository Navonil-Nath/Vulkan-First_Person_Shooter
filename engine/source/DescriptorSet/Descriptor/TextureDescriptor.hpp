#ifndef NORMAL_DESCRIPTOR_CLASS
#define NORMAL_DESCRIPTOR_CLASS

#include<vulkan/vulkan.h>
#include<iostream>
#include<stdexcept>

class TextureDescriptor{
    public:

    TextureDescriptor()=default;
    TextureDescriptor(const TextureDescriptor&)=delete;
    TextureDescriptor& operator=(const TextureDescriptor&)=delete;

    void CreateNormalDescriptor(VkDevice Device,VkDescriptorSet& set,VkImageView baseImageView,VkImageView normalImageView,VkImageView MetallicImageView,VkSampler sampler);
};

#endif

//these descriptors are to be used once per model