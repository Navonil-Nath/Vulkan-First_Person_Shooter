#ifndef REFLECTION_DESCRIPTOR_CLASS
#define REFLECTION_DESCRIPTOR_CLASS
#include<vulkan/vulkan.h>
#include<stdexcept>
#include<iostream>

class ReflectionDescriptor{
    public:
    ReflectionDescriptor()=default;
    ReflectionDescriptor(const ReflectionDescriptor&)=delete;
    ReflectionDescriptor& operator=(const ReflectionDescriptor&)=delete;

    void CreateReflectionCubeMapDescriptor(VkDescriptorSet& set,VkDevice device,VkSampler sampler,VkImageView RefCubeMapImageView);

};

#endif
/*
  This descriptor contains the VkImage to the memeory which will contain the reflection images on the surface ofa reflecting object
  ->to be declared once per reflecting object

*/