#ifndef REFLECTION_DESCRIPTOR_CLASS
#define REFLECTION_DESCRIPTOR_CLASS
#include<vulkan/vulkan.h>
#include<stdexcept>
#include<iostream>

class ReflectionDescriptor{
    public:
    ReflectionDescriptor(const ReflectionDescriptor&)=delete;
    ReflectionDescriptor& operator=(const ReflectionDescriptor&)=delete;

    void CreateReflectionCubeMapDescriptor(VkDescriptorSet& set,VkDevice device,VkSampler sampler,VkImageView RefCubeMapImageView);

};

#endif