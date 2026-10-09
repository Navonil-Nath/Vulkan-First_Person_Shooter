/*
creating the descriptor set layout
*/
#ifndef DESCRIPTOR_SET_LAYOUT_CLASS
#define DESCRIPTOR_SET_LAYOUT_CLASS
#include<vulkan/vulkan.h>
#include<iostream>
#include<glm/glm.hpp>
#include<stdexcept>
#include<cstdint>
#include<vector>

class DescriptorSetLayout{
    public:
        DescriptorSetLayout(VkDevice device,const std::vector<VkDescriptorSetLayoutBinding>& bindings);
        ~DescriptorSetLayout();

        DescriptorSetLayout(const DescriptorSetLayout&)=delete;
        DescriptorSetLayout& operator=(const DescriptorSetLayout&)=delete;

        VkDescriptorSetLayout get(){return m_descriptorSetLayout;}


    private:
        VkDescriptorSetLayout m_descriptorSetLayout{VK_NULL_HANDLE};
        VkDevice m_device{VK_NULL_HANDLE};

        void CreateSetLayout(const std::vector<VkDescriptorSetLayoutBinding>& bindings);


};

#endif