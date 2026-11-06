#ifndef SKYBOX_DESCRIPTOR_CLASS
#define SKYBOX_DESCRIPTOR_CLASS
#include<vulkan/vulkan.hpp>
#include<stdexcept>


class SkyBoxDescriptor{
    public:

    SkyBoxDescriptor()=default;
    SkyBoxDescriptor(const SkyBoxDescriptor&)=delete;
    SkyBoxDescriptor& operator=(const SkyBoxDescriptor&)=delete;

    void CreateSkyBoxDescriptor(VkDevice device,VkSampler sampler,VkImageView view,VkDescriptorSet& set);
};
#endif