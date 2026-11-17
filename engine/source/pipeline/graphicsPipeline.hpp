#ifndef GRAPHICSPIPELINE_CLASS
#define GRAPHICSPIPELINE_CLASS

#include<vulkan/vulkan.h>
#include<stdexcept>
#include<string>

class GraphicsPipeline{
    public:
        GraphicsPipeline(VkDevice device,VkRenderPass renderpass,VkPipelineLayout pipelineLayout,VkExtent2D swapchainExtent,const std::string& vertex_shaderPath,const std::string& fragment_shaderPath,bool isSkyBox);
        ~GraphicsPipeline();

        GraphicsPipeline(const GraphicsPipeline&)=delete;
        GraphicsPipeline& operator=(const GraphicsPipeline&)=delete;

        VkPipeline get(){return m_graphicsPipeline;}



    private:
        VkPipeline m_graphicsPipeline{VK_NULL_HANDLE};
        void CreateGraphicsPipeline(VkRenderPass renderpass,VkPipelineLayout pipelineLayout,VkExtent2D swapchainExtent,const std::string& vertex_shaderPath,const std::string& fragment_shaderPath,bool isSkybox);
        VkDevice m_device{VK_NULL_HANDLE};

};  

#endif


//this graphics will be used for both the skybox creation and the model loading 