#include"uniformBufferDescriptor.hpp"
#include"UniformBuffer.hpp"

void UniformBufferDescriptor::CreateUniformBufferDescriptor(VkDevice device,VkDescriptorSet& set,VkBuffer uniformBuffer){
    //-------put them to the binding 0---------------
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer=uniformBuffer;
    bufferInfo.offset=0;
    bufferInfo.range=sizeof(UniformBufferObject);

    VkWriteDescriptorSet descriptorUniformBuffer{};
    descriptorUniformBuffer.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorUniformBuffer.dstSet=set;
    descriptorUniformBuffer.dstBinding=0;
    descriptorUniformBuffer.dstArrayElement=0;
    descriptorUniformBuffer.descriptorType=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorUniformBuffer.descriptorCount=1;
    descriptorUniformBuffer.pBufferInfo=&bufferInfo;


    vkUpdateDescriptorSets(device,1,& descriptorUniformBuffer,0,nullptr);
}