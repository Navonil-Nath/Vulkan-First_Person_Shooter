#ifndef NORMAL_DESCRIPTOR_CLASS
#define NORMAL_DESCRIPTOR_CLASS

#include<vulkan/vulkan.h>
#include<iostream>
#include<stdexcept>

class NormalDescriptor{
    public:


    NormalDescriptor(const NormalDescriptor&)=delete;
    NormalDescriptor& operator=(const NormalDescriptor&)=delete;

    void CreateNormalDescriptor(VkDevice Device,VkDescriptorSet& set,VkImageView baseImageView,VkImageView normalImageView,VkImageView MetallicRoughnessValue,VkSampler sampler);
};

#endif