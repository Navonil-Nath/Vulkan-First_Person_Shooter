#ifndef DESCRIPTOR_POOL_CLASS
#define DESCRIPTOR_POOL_CLASS
#include<vulkan/vulkan.h>
#include<stdexcept>
#include<iostream>
#include"DescriptorSetLayout.hpp"

class DescriptorPool{
    public:
    DescriptorPool(VkDevice device);
    ~DescriptorPool();

    DescriptorPool(const DescriptorPool&)=delete;
    DescriptorPool& operator=(const DescriptorPool&)=delete;

    VkDescriptorPool get(){return m_Descriptorpool;}
    private:
    VkDescriptorPool m_Descriptorpool{VK_NULL_HANDLE};
    VkDevice m_device{VK_NULL_HANDLE};

    void CreateDescriptorPool();

};

#endif