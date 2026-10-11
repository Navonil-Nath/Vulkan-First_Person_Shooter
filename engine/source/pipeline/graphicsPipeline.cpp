#include"graphicsPipeline.hpp"
#include"shaderModule.hpp"
#include"vertex.hpp"

GraphicsPipeline::GraphicsPipeline(VkDevice device,VkRenderPass renderpass,VkPipelineLayout pipelineLayout,VkExtent2D swapchainExtent):m_device(device){
    CreateGraphicsPipeline(device,renderpass,pipelineLayout,swapchainExtent);
}

GraphicsPipeline::~GraphicsPipeline(){
    if(m_graphicsPipeline!=VK_NULL_HANDLE){
        vkDestroyPipeline(m_device,m_graphicsPipeline,nullptr);
    }

}

void GraphicsPipeline::CreateGraphicsPipeline(VkDevice device,VkRenderPass renderpass,VkPipelineLayout pipelineLayout,VkExtent2D swapchainExtent){
    ShaderModule vertexModule(m_device,"base.vert.spv");
    ShaderModule fragmentModule(m_device,"base.frag.spv");

    VkPipelineShaderStageCreateInfo vertexShaderstageInfo{};
    vertexShaderstageInfo.stage=VK_SHADER_STAGE_VERTEX_BIT;
    vertexShaderstageInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertexShaderstageInfo.module=vertexModule.get();
    vertexShaderstageInfo.pName="main";

    VkPipelineShaderStageCreateInfo fragmentShaderstageInfo{};
    fragmentShaderstageInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragmentShaderstageInfo.stage=VK_SHADER_STAGE_FRAGMENT_BIT;

    fragmentShaderstageInfo.module=fragmentModule.get();
    fragmentShaderstageInfo.pName="main";


    VkPipelineShaderStageCreateInfo shaderStages[]={vertexShaderstageInfo,fragmentShaderstageInfo};

    //getting the vertex binding and attribute descriptions

    auto bindingDescription=Vertex::getBindingDescription();
    auto attributeDescription=Vertex::getAllAttributes();


    VkPipelineVertexInputStateCreateInfo vertexDescription{};
    vertexDescription.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexDescription.vertexBindingDescriptionCount=1;
    vertexDescription.pVertexBindingDescriptions= &bindingDescription;
    vertexDescription.vertexAttributeDescriptionCount=static_cast<uint32_t>(attributeDescription.size());
    vertexDescription.pVertexAttributeDescriptions=attributeDescription.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType=VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;


    VkViewport viewports{0.0f,0.0f,static_cast<uint32_t>(swapchainExtent.width),static_cast<uint32_t>(swapchainExtent.height),0.0f,1.0f};
    //determines the mapping of the game window to the glfw window
    VkRect2D window_fit{{0.0f,0.0f},swapchainExtent}; //determines from where the game window should start in the glfw window
    
    VkPipelineViewportStateCreateInfo  viewportGame{};
    viewportGame.sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportGame.viewportCount=1;
    viewportGame.pViewports=&viewports;
    viewportGame.scissorCount=1;
    viewportGame.pScissors=&window_fit;


    VkPipelineRasterizationStateCreateInfo reterizationInfo{};
    reterizationInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    reterizationInfo.polygonMode=VK_POLYGON_MODE_FILL;
    reterizationInfo.lineWidth=1.0f;
    reterizationInfo.cullMode=VK_CULL_MODE_BACK_BIT;
    reterizationInfo.frontFace=VK_FRONT_FACE_COUNTER_CLOCKWISE;

    //we will stick to the default 1bit sampling per fragment fornow

    VkPipelineMultisampleStateCreateInfo sampleCreateInfo{};
    sampleCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    sampleCreateInfo.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachments{}; //whuch are the coloe channels the gpu is allowed to write with.
    colorBlendAttachments.colorWriteMask=VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    colorBlendAttachments.blendEnable=VK_FALSE; //no color belndng woth the previous buffer .complete rewrite


    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType=VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.attachmentCount=1;
    colorBlending.pAttachments=&colorBlendAttachments;

    //now defining the stage when it comes for the gpu to fill in the depth image

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    depthStencil.sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable=VK_TRUE;
    depthStencil.depthWriteEnable=VK_TRUE;
    depthStencil.depthCompareOp=VK_COMPARE_OP_LESS;
    depthStencil.depthBoundsTestEnable=VK_FALSE;
    depthStencil.stencilTestEnable=VK_FALSE;


    //now create the final pipleine

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount=2; //vertex anf fragment
    pipelineInfo.pStages=shaderStages;
    pipelineInfo.pVertexInputState=&vertexDescription;
    pipelineInfo.pInputAssemblyState=&inputAssembly;
    pipelineInfo.pViewportState=&viewportGame;
    pipelineInfo.pRasterizationState=&reterizationInfo;
    pipelineInfo.pMultisampleState=&sampleCreateInfo;
    pipelineInfo.pDepthStencilState=&depthStencil;
    pipelineInfo.pColorBlendState=&colorBlending;
    pipelineInfo.layout=pipelineLayout;
    pipelineInfo.renderPass=renderpass;


    if(vkCreateGraphicsPipelines(m_device,VK_NULL_HANDLE,1,&pipelineInfo,nullptr,&m_graphicsPipeline)!=VK_SUCCESS){
        throw std::runtime_error("failled to create graphis pipleine");
    }
    
}
