#ifndef TEXTURE_SAMPLER_CLASS
#define TEXTURE_SAMPLER_CLASS

#include<vulkan/vulkan.h>
#include<iostream>
#include<stdexcept>

enum class Sampler{

    Repeat,
    ClampToEdge
};



class TextureSampler{
    public:

    TextureSampler(VkDevice device,Sampler address=Sampler::Repeat);
    ~TextureSampler();

    TextureSampler(const TextureSampler&)=delete;
    TextureSampler& operator=(const TextureSampler&)=delete;

    private:
    VkDevice m_device{VK_NULL_HANDLE};
    VkSampler m_sampler{VK_NULL_HANDLE};
    void CreateSampler(Sampler address);
};

#endif