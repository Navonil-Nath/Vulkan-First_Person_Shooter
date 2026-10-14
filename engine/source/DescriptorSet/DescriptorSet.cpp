#include"DescriptorSet.hpp"


DescriptorSet::DescriptorSet(VkDevice device,VkDescriptorSetLayout layout,VkDescriptorPool pool):m_device(device){
    CreateDescriptorSet( layout,pool);
}

DescriptorSet::~DescriptorSet(){
    std::cout<<"Descriptor set deallocated"<<std::endl;
}

void DescriptorSet::CreateDescriptorSet(VkDescriptorSetLayout layout,VkDescriptorPool pool){
    VkDescriptorSetAllocateInfo allocateInfo{};
    allocateInfo.sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocateInfo.descriptorPool=pool;
    allocateInfo.descriptorSetCount=1;
    allocateInfo.pSetLayouts=&layout;
    
    if(vkAllocateDescriptorSets(m_device,&allocateInfo,&m_DescriptorSet)!=VK_SUCCESS){
        throw std::runtime_error("the descriptor set coudn't be formed");
    }
}
