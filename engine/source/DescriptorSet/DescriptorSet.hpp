#ifndef DESCRIPTOR_SET_CLASS
#define DESCRIPTOR_SET_CLASS
#include"DescriptorPool.hpp"
#include<vulkan/vulkan.hpp>
#include<iostream>
#include<stdexcept>
#include<array>

class DescriptorSet{
    public:

    DescriptorSet(VkDevice device,VkDescriptorSetLayout layout,VkDescriptorPool pool);
    ~DescriptorSet();

    DescriptorSet(const DescriptorSet&)=delete;
    DescriptorSet& operator=(const DescriptorSet&)=delete;
    VkDescriptorSet get(){return m_DescriptorSet;}

    private:
    VkDevice m_device{VK_NULL_HANDLE};
    VkDescriptorSet m_DescriptorSet{VK_NULL_HANDLE};
    void CreateDescriptorSet(VkDescriptorSetLayout layout,VkDescriptorPool pool);
    

};

#endif