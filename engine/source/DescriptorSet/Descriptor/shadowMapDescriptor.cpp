#include"shadowMapDescriptor.hpp"

void ShadowMapDescriptor::CreateShadowMapDescriptor(VkDevice device,VkSampler sampler,VkDescriptorSet& set,VkImageView imageView){
    //attach the descriptor to the bnding 0 of the set
    VkDescriptorImageInfo shadowMapInfo{};
    shadowMapInfo.imageLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    shadowMapInfo.imageView=imageView;
    shadowMapInfo.sampler=sampler;

    VkWriteDescriptorSet shadowMapWrite{};
    shadowMapWrite.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    shadowMapWrite.dstSet=set;
    shadowMapWrite.dstBinding=0;
    shadowMapWrite.dstArrayElement=0;
    shadowMapWrite.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    shadowMapWrite.descriptorCount=1;
    shadowMapWrite.pImageInfo=&shadowMapInfo;    

    vkUpdateDescriptorSets(device,1,&shadowMapWrite,0,nullptr);


}