#ifndef SHADOW_MAP_DESCRIPTOR_CLASS
#define SHADOW_MAP_DESCRTPTOR_CLASS
#include<vulkan/vulkan.hpp>
#include<iostream>
class ShadowMapDescriptor{
    public:
    ShadowMapDescriptor()=default;
    ShadowMapDescriptor(const ShadowMapDescriptor&)=delete;
    ShadowMapDescriptor &operator=(const ShadowMapDescriptor&)=delete;

    void CreateShadowMapDescriptor(VkDevice device,VkSampler sampler,VkDescriptorSet& set,VkImageView imageView);


};
#endif

/*
this class shall establish a descriptor set containing a image view which shall contaain a image that will contain the
shaodw depth data wrt to an illuminating object eg a 'light source' this will then be processed by the renderer into the main
frambeuffer depth image to cast regions of darkness thereby creating our shadows

this descriptor should be created once for every illuminating objects
*/
