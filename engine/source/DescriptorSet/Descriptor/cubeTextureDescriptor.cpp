#include"cubeTextureDescriptor.hpp"

void cubeTextureDescriptor::createTextureDescriptor(VkDevice device,VkDescriptorSet& set,VkSampler sampler,std::vector<VkImageView>cubeTextures){

//--------put the descriptors to the binding 0---------
    std::vector<VkDescriptorImageInfo> image_infos;
    image_infos.reserve(cubeTextures.size());
    for(VkImageView image_view:cubeTextures){
        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView=image_view;
        imageInfo.sampler=sampler;
    
        image_infos.push_back(imageInfo);

    }
    VkWriteDescriptorSet cubeTextureDescriptors{};
    cubeTextureDescriptors.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    cubeTextureDescriptors.dstSet=set;
    cubeTextureDescriptors.dstBinding=1;
    cubeTextureDescriptors.dstArrayElement=0;
    cubeTextureDescriptors.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    cubeTextureDescriptors.descriptorCount=static_cast<uint32_t>(image_infos.size());
    cubeTextureDescriptors.pImageInfo=image_infos.data();
    

    vkUpdateDescriptorSets(device,1,&cubeTextureDescriptors,0,nullptr);

}