#ifndef UNIFORM_BUFFER_DESCRIPTOR_CLASS
#define UNIFORM_BUFFER_DESCRIPTOR_CLASS
#include<vulkan/vulkan.hpp>
#include<iostream>
#include<stdexcept>


class UniformBufferDescriptor{
    public:

    UniformBufferDescriptor()=default;
    UniformBufferDescriptor(const UniformBufferDescriptor&)=delete;
    UniformBufferDescriptor &operator=(const UniformBufferDescriptor&)=delete;
    
    void CreateUniformBufferDescriptor(VkDevice device,VkDescriptorSet& set,VkBuffer uniformBuffer);
};
#endif