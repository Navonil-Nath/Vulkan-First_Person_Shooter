#include"TextureSampler.hpp"


TextureSampler::TextureSampler(VkDevice device,Sampler address):m_device(device){

    CreateSampler(address);
}

TextureSampler::~TextureSampler(){
    if(m_sampler!=VK_NULL_HANDLE){
        vkDestroySampler(m_device,m_sampler,nullptr);
    }
}

void TextureSampler::CreateSampler(Sampler address){
    VkSamplerAddressMode addressMode=(address==Sampler::Repeat)?VK_SAMPLER_ADDRESS_MODE_REPEAT:VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    
    
    VkSamplerCreateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    createInfo.magFilter=VK_FILTER_LINEAR;
    createInfo.minFilter=VK_FILTER_LINEAR;
    createInfo.addressModeU=addressMode;
    createInfo.addressModeV=addressMode;
    createInfo.addressModeW=addressMode;
    createInfo.anisotropyEnable=VK_TRUE;
    createInfo.maxAnisotropy=16.0f;
    createInfo.borderColor=VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    createInfo.unnormalizedCoordinates=VK_FALSE;
    createInfo.compareEnable=VK_FALSE;
    createInfo.compareOp=VK_COMPARE_OP_ALWAYS;
    createInfo.mipmapMode=VK_SAMPLER_MIPMAP_MODE_LINEAR;
    createInfo.mipLodBias=0.0f;
    createInfo.minLod=0.0f;
    createInfo.maxLod=0.0f;

    if(vkCreateSampler(m_device,&createInfo,nullptr,&m_sampler)!=VK_SUCCESS){
        throw std::runtime_error("the texture sampler for the descriptor coudn't be formed");
    }    

}

