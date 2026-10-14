#ifndef DIFFUSE_IMAGE_DESCRIPTOR_CLASS
#define DIFFUSE_IMAGE_DESCRIPTOR_CLASS

#include<vulkan/vulkan.h>
#include<iostream>
#include<vector>

class DiffuseImage{
    public:
        DiffuseImage(const DiffuseImage&)=delete;
        DiffuseImage& operator=(const DiffuseImage&)=delete;

        void CreateDescriptor(VkDevice device,VkDescriptorSet& set,VkBuffer uniformBuffer,const std::vector<VkImageView>& cubeImageViews,VkSampler cubeImagesSampler,VkImageView skyboxImageView,VkSampler skyboxSampler,VkImageView shadowMapView,VkSampler shadowMapSampler);


};

#endif