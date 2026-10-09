#include"DescriptorSetLayout.hpp"

DescriptorSetLayout::DescriptorSetLayout(VkDevice device,const std::vector<VkDescriptorSetLayoutBinding>& bindings):m_device(device){
    CreateSetLayout(bindings);
}

void DescriptorSetLayout::CreateSetLayout(const std::vector<VkDescriptorSetLayoutBinding>& bindings){
    VkDescriptorSetLayoutCreateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    createInfo.bindingCount=static_cast<uint32_t>(bindings.size());
    createInfo.pBindings=bindings.data();
    

    if(vkCreateDescriptorSetLayout(m_device,&createInfo,nullptr,&m_descriptorSetLayout)!=VK_SUCCESS){
        throw std::runtime_error("failled to create the layout of the descrtor set");
    }   

}

DescriptorSetLayout::~DescriptorSetLayout(){
    if(m_descriptorSetLayout!=VK_NULL_HANDLE){
        vkDestroyDescriptorSetLayout(m_device,m_descriptorSetLayout,nullptr);
    }
}