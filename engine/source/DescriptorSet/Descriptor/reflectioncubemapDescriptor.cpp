#include"reflectioncubemapDescriptor.hpp"
//this descriptor shall contain the cubemapimage for the reflection data of a reflective 3d model


void ReflectionDescriptor::CreateReflectionCubeMapDescriptor(VkDescriptorSet& set,VkDevice device,VkSampler sampler,VkImageView RefCubeMapImageView){
    VkDescriptorImageInfo descriptorInfo{};
    descriptorInfo.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    descriptorInfo.imageView=RefCubeMapImageView;
    descriptorInfo.sampler=sampler;

    VkWriteDescriptorSet writeSet{};
    writeSet.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeSet.dstSet=set;
    writeSet.dstBinding=0;
    writeSet.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeSet.descriptorCount=1;
    writeSet.pImageInfo=&descriptorInfo;

    vkUpdateDescriptorSets(device,1,&writeSet,0,nullptr);
}