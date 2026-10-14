#include"DescriptorPool.hpp"
#include<vector>
#include<array>



DescriptorPool::DescriptorPool(VkDevice device):m_device(device){
    CreateDescriptorPool();    

}
DescriptorPool::~DescriptorPool(){

}


void DescriptorPool::CreateDescriptorPool(){

    //specifying the maximum descriptors allowed
    //buffers
    std::array<VkDescriptorPoolSize,2>poolSizes;
    poolSizes[0].type=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount=500;

    //texture

    poolSizes[1].type=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount=5000;

    VkDescriptorPoolCreateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.poolSizeCount=static_cast<uint32_t>(poolSizes.size());
    createInfo.pPoolSizes=poolSizes.data();
    createInfo.flags=VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT; //this allows to free descriptors indivisually
    createInfo.maxSets=3000; //the no of descriptor sets that we can create from this pool    

    if(vkCreateDescriptorPool(m_device,&createInfo,nullptr,&m_Descriptorpool)!=VK_SUCCESS){
        throw std::runtime_error("the descriptor pool cannot be created");
    }



}
