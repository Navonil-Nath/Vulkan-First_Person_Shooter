#include"skyboxDescriptor.hpp"

void SkyBoxDescriptor::CreateSkyBoxDescriptor(VkDevice device,VkSampler sampler,std::vector<VkImageView>Skyboxtexture_Views,VkDescriptorSet& set){
    //-------put them to the binding 0------------
    std::vector<VkDescriptorImageInfo>image_infos;
    image_infos.reserve(Skyboxtexture_Views.size());


    for(VkImageView view:Skyboxtexture_Views){
         VkDescriptorImageInfo SkyboxDescriptor{};
         SkyboxDescriptor.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
         SkyboxDescriptor.sampler=sampler;
         SkyboxDescriptor.imageView=view;
         image_infos.push_back(SkyboxDescriptor);

    }

    VkWriteDescriptorSet skyBoxDescriptorWritter{};
    skyBoxDescriptorWritter.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    skyBoxDescriptorWritter.dstSet=set;
    skyBoxDescriptorWritter.dstBinding=0;
    skyBoxDescriptorWritter.dstArrayElement=0;
    skyBoxDescriptorWritter.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    skyBoxDescriptorWritter.descriptorCount=static_cast<uint32_t>(image_infos.size());
    skyBoxDescriptorWritter.pImageInfo=image_infos.data();

    vkUpdateDescriptorSets(device,1,&skyBoxDescriptorWritter,0,nullptr);
}

