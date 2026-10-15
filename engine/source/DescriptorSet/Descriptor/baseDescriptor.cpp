#include"baseDescriptor.hpp"
#include"UniformBuffer.hpp"


void DiffuseImage::CreateDescriptor(VkDevice device,VkDescriptorSet& set,VkBuffer uniformBuffer,const std::vector<VkImageView>& cubeImageViews,VkSampler cubeImagesSampler,VkImageView skyboxImageView,VkSampler skyboxSampler,VkImageView shadowMapView,VkSampler shadowMapSampler){
    //binding 0 uniform buffer(UniformBufferObject) ,this dewcriptor shall contain the uniform buffer at binding 0;
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer=uniformBuffer;
    bufferInfo.offset= 0;
    bufferInfo.range=sizeof(UniformBufferObject);

    VkWriteDescriptorSet descriptorUniformBufferObject{};
    descriptorUniformBufferObject.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorUniformBufferObject.dstSet=set;
    descriptorUniformBufferObject.dstBinding=0;
    descriptorUniformBufferObject.dstArrayElement=0;
    descriptorUniformBufferObject.descriptorType=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorUniformBufferObject.descriptorCount=1;
    descriptorUniformBufferObject.pBufferInfo=&bufferInfo;

    vkUpdateDescriptorSets(device,1,&descriptorUniformBufferObject,0,nullptr);
    
    

    //binding 1  will contain an array of descriptors each holding an VkImageView referencing to an VkImage 

    std::vector<VkDescriptorImageInfo> image_infos;
    image_infos.reserve(cubeImageViews.size());

    for(VkImageView view:cubeImageViews){
        VkDescriptorImageInfo info{};
        info.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        info.imageView=view;
        info.sampler=cubeImagesSampler;
        image_infos.push_back(info);
    }

    VkWriteDescriptorSet CubeMapViewsInfo{};
    CubeMapViewsInfo.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    CubeMapViewsInfo.dstSet=set;
    CubeMapViewsInfo.dstBinding=1;
    CubeMapViewsInfo.dstArrayElement=0;
    CubeMapViewsInfo.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    CubeMapViewsInfo.descriptorCount=static_cast<uint32_t>(image_infos.size());
    CubeMapViewsInfo.pImageInfo=image_infos.data();

    vkUpdateDescriptorSets(device,1,&CubeMapViewsInfo,0,nullptr);

    //binding 2 shall contain the shadow map texture

    VkDescriptorImageInfo shadowMapInfo{};
    shadowMapInfo.imageLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    shadowMapInfo.imageView=shadowMapView;
    shadowMapInfo.sampler=shadowMapSampler;

    VkWriteDescriptorSet shadowmapwrite{};
    shadowmapwrite.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    shadowmapwrite.dstSet=set;
    shadowmapwrite.dstBinding=2;
    shadowmapwrite.dstArrayElement=0;
    shadowmapwrite.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    shadowmapwrite.descriptorCount=1;
    shadowmapwrite.pImageInfo=&shadowMapInfo;

    vkUpdateDescriptorSets(device,1,&shadowmapwrite,0,nullptr);



    //binding 3 shall contain the descriptor holding the skybox image view

    VkDescriptorImageInfo cubeMapDescriptor{};
    cubeMapDescriptor.imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    cubeMapDescriptor.imageView=skyboxImageView;
    cubeMapDescriptor.sampler=skyboxSampler;


    VkWriteDescriptorSet skyboxWritter{};
    skyboxWritter.sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    skyboxWritter.dstSet=set;
    skyboxWritter.dstBinding=3;
    skyboxWritter.dstArrayElement=0;
    skyboxWritter.descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; //meaning the VkImage had many layers holding textures
    skyboxWritter.descriptorCount=1;
    skyboxWritter.pImageInfo= &cubeMapDescriptor;



    vkUpdateDescriptorSets(device,1,&skyboxWritter,0,nullptr);



}