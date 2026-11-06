#include"skyboxDescriptor.hpp"

void SkyBoxDescriptor::CreateSkyBoxDescriptor(VkDevice device,VkSampler sampler,VkImageView view,VkDescriptorSet& set){
    //-------put them to the binding 0------------
    VkDescriptorImageInfo SkyBoxDescriptor{};
    SkyBoxDescriptor.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    SkyBoxDescriptor.imageView=view;
    SkyBoxDescriptor.sampler=sampler;

    VkWriteDescriptorSet skyBoxDescriptorWritter{};
    skyBoxDescriptorWritter.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    skyBoxDescriptorWritter.dstSet=set;
    skyBoxDescriptorWritter.dstBinding=0;
    skyBoxDescriptorWritter.dstArrayElement=0;
    skyBoxDescriptorWritter.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    skyBoxDescriptorWritter.descriptorCount=1;
    skyBoxDescriptorWritter.pImageInfo=&SkyBoxDescriptor;


    vkUpdateDescriptorSets(device,1,& skyBoxDescriptorWritter,0,nullptr);
}