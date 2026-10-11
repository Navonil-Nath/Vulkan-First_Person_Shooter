/*
the pipelineLayout takes in the vector of the VkDescriptorSetLayouts and then assigns each set to each layout 
eg:if a vector say std::vector<VkDescriptorSetLayout> vectors is passed to the grphics pipleinelayout then the vulkan assigns 
set0-->vectors[0],
set1-->vectors[1],..

*/
#ifndef PIPELINELAYOUT_CLASS
#define PIPELINELAYOUT_CLASS
#include<iostream>
#include<stdexcept>
#include<vector>
#include<vulkan/vulkan.h>


class PipelineLayout{
    public:
        
        PipelineLayout(VkDevice device,std::vector<VkDescriptorSetLayout>Setlayouts);
        ~PipelineLayout();

        PipelineLayout(const PipelineLayout&)=delete;
        PipelineLayout& operator=(const PipelineLayout&)=delete;

        void createPipelineLayout(std::vector<VkDescriptorSetLayout>Setlayouts);
        VkPipelineLayout get(){return m_pipelineLayout;}


    private:
        VkDevice m_device{VK_NULL_HANDLE};
        VkPipelineLayout m_pipelineLayout{VK_NULL_HANDLE};

};

#endif