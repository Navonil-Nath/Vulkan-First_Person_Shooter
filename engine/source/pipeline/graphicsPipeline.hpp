#ifndef GRAPHICSPIPELINE_CLASS
#define GRAPHICSPIPELINE_CLASS

#include<vulkan/vulkan.h>
#include<stdexcept>

class GraphicsPipeline{
    public:
        GraphicsPipeline(VkDevice device,VkRenderPass renderpass,VkPipelineLayout pipelineLayout,VkExtent2D swapchainExtent);
        ~GraphicsPipeline();

        GraphicsPipeline(const GraphicsPipeline&)=delete;
        GraphicsPipeline& operator=(const GraphicsPipeline&)=delete;

        VkPipeline get(){return m_graphicsPipeline;}



    private:
        VkPipeline m_graphicsPipeline{VK_NULL_HANDLE};
        void CreateGraphicsPipeline(VkDevice device,VkRenderPass renderpass,VkPipelineLayout pipelineLayout,VkExtent2D swapchainExtent);
        VkDevice m_device{VK_NULL_HANDLE};

};  

#endif