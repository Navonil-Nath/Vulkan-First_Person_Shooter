#include"renderpass.hpp"
#include<algorithm>
#include<array>
#include<cstdlib>
#include<stdexcept>

RenderPass::RenderPass(VkFormat colorFormat,VkFormat depthFormat,VkDevice device):m_device(device){
    CreateRenderPass(colorFormat,depthFormat);
}

RenderPass::~RenderPass(){
    if(m_device!=VK_NULL_HANDLE){
        vkDestroyRenderPass(m_device,m_renderPass,nullptr);
    }
}

void RenderPass::CreateRenderPass(VkFormat colorFormat,VkFormat depthFormat){
    //first we will give the color image description

    VkAttachmentDescription colorAttachment{};
    colorAttachment.format=colorFormat;
    colorAttachment.samples=VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    //since we will be implementing shadows in our engine we need to store the previous fram data
    colorAttachment.storeOp=VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED; //ie we are letting the gpu decidethe layoutin the raw image ,ie it will decide the best optimal one for itself
    colorAttachment.finalLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


    VkAttachmentReference colorReference{};
    colorReference.attachment=0; //define the binding point in the pAttachemnt
    colorReference.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; //let the gpu decide the best layout



    //give the desription of the depth image

    VkAttachmentDescription depthAttachment;
    depthAttachment.format=depthFormat;
    depthAttachment.samples=VK_SAMPLE_COUNT_1_BIT;
    depthAttachment.loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR; //ie clear the image off the data from the previous frae to be used by the next frame
    depthAttachment.storeOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachment.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED; //same as of the color image letting the gpu define the best layout in the raw image for optimisation 
    depthAttachment.finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    


    VkAttachmentReference depthAttachmentRef{};
    depthAttachmentRef.attachment=1; //define the binding point of the depth image in the pAttachemnt
    depthAttachmentRef.layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


    //now define the subpass
    //a subpass is what encapsulates the graphics pipeline


    VkSubpassDescription subPass{};
    subPass.pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS;
    subPass.colorAttachmentCount=1;  //defines how many color images are attached to the pAttachment
    subPass.pColorAttachments=&colorReference;
    subPass.pDepthStencilAttachment=&depthAttachmentRef;
    
    std::array<VkAttachmentDescription,2>attachments={colorAttachment,depthAttachment};
    

    //create the renderpass

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount=static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments=attachments.data();
    renderPassInfo.subpassCount=1; //defines how many graphics pripleines we want to intiate per renderpass here only 1 as each subpass starts only 1 graphics pipeline operation
    renderPassInfo.pSubpasses=&subPass;


    if(vkCreateRenderPass(m_device,&renderPassInfo,nullptr,&m_renderPass)!=VK_SUCCESS){
        throw std::runtime_error("the renderpass coudn't be created");
    }   

}




