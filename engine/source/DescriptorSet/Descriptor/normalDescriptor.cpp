#include"normalDescriptor.hpp"

void NormalDescriptor::CreateNormalDescriptor(VkDevice Device,VkDescriptorSet set,VkImageView baseImageView,VkImageView normalImageView,VkImageView MetallicRoughnessview,VkSampler sampler){
    //binding =0 diffuse image
    VkDescriptorImageInfo diffuseImageInfo{};
    diffuseImageInfo.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    diffuseImageInfo.imageView=baseImageView;
    diffuseImageInfo.sampler=sampler;

    VkWriteDescriptorSet writeBaseDescriptor{};
    writeBaseDescriptor.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeBaseDescriptor.dstSet=set;
    writeBaseDescriptor.dstBinding=0;
    writeBaseDescriptor.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeBaseDescriptor.descriptorCount=1;
    writeBaseDescriptor.pImageInfo=&diffuseImageInfo;

    vkUpdateDescriptorSets(Device,1,&writeBaseDescriptor,0,nullptr);


    //binding =1 normal image
    VkDescriptorImageInfo normalImageInfo{};
    normalImageInfo.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    normalImageInfo.imageView=normalImageView;
    normalImageInfo.sampler=sampler;

    VkWriteDescriptorSet writeNormalDescriptor{};
    writeNormalDescriptor.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeNormalDescriptor.dstSet=set;
    writeNormalDescriptor.dstBinding=1;
    writeNormalDescriptor.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeNormalDescriptor.descriptorCount=1;
    writeNormalDescriptor.pImageInfo=&normalImageInfo;

    vkUpdateDescriptorSets(Device,1,&writeNormalDescriptor,0,nullptr);


    //binding =2 metallic roughness value
    VkDescriptorImageInfo MetallicRoughnessInfo{};
    MetallicRoughnessInfo.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    MetallicRoughnessInfo.imageView=MetallicRoughnessview;
    MetallicRoughnessInfo.sampler=sampler;

    VkWriteDescriptorSet writeMetallicDescriptor{};
    writeNormalDescriptor.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeNormalDescriptor.dstSet=set;
    writeNormalDescriptor.dstBinding=2;
    writeNormalDescriptor.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeNormalDescriptor.descriptorCount=1;
    writeNormalDescriptor.pImageInfo=&MetallicRoughnessInfo;

    vkUpdateDescriptorSets(Device,1,&writeMetallicDescriptor,0,nullptr);

}

//remember the descriptor and descriptor sets are allocted in the gpu so the shaders can directlly acess them