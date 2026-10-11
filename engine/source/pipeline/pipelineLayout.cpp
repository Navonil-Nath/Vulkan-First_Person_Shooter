#include"pipelineLayout.hpp"
#include"pushConstant.hpp"


PipelineLayout::PipelineLayout(VkDevice device,std::vector<VkDescriptorSetLayout>SetLayouts):m_device(device){
    createPipelineLayout(SetLayouts);
}


PipelineLayout::~PipelineLayout(){
    if(m_pipelineLayout!=VK_NULL_HANDLE){
        vkDestroyPipelineLayout(m_device,m_pipelineLayout,nullptr);
    }
}

void PipelineLayout::createPipelineLayout(std::vector<VkDescriptorSetLayout>SetLayouts){

    VkPipelineLayoutCreateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    createInfo.setLayoutCount=static_cast<uint32_t>(SetLayouts.size());
    createInfo.pSetLayouts=SetLayouts.data();


    //include the pish constant data
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags=VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset=0;
    pushConstantRange.size=sizeof(PushConstantObject);


    createInfo.pushConstantRangeCount=1;
    createInfo.pPushConstantRanges=&pushConstantRange;

    if(vkCreatePipelineLayout(m_device,&createInfo,nullptr,&m_pipelineLayout)!=VK_SUCCESS){
        throw std::runtime_error("the pipleine layoutcoudn't be formed");
    }

}