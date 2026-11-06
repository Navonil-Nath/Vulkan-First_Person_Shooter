#ifndef DIFFUSE_IMAGE_DESCRIPTOR_CLASS
#define DIFFUSE_IMAGE_DESCRIPTOR_CLASS

#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>


class BaseDescriptor {
public:
  BaseDescriptor() = default;
  BaseDescriptor(const BaseDescriptor &) = delete;
  BaseDescriptor &operator=(const BaseDescriptor &) = delete;

  void CreateDescriptor(VkDevice device, VkDescriptorSet &set,
                        VkBuffer uniformBuffer,
                        const std::vector<VkImageView> &cubeImageViews,
                        VkSampler cubeImagesSampler,
                        VkImageView skyboxImageView, VkSampler skyboxSampler,
                        VkImageView shadowMapView, VkSampler shadowMapSampler);
};

#endif