#include"framebuffer.hpp"


FrameBuffer::FrameBuffer(VkDevice device,std::vector<VkImageView>swapColorImagesViews,VkImageView depthImageView,VkRenderPass renderpass,VkExtent2D extent){
    CreateFrameBuffer(swapColorImagesViews,depthImageView,renderpass,extent);


}

FrameBuffer::~FrameBuffer(){
    for(VkFramebuffer buffer:m_framebuffer){
        if(buffer!=VK_NULL_HANDLE){
            vkDestroyFramebuffer(m_device,buffer,nullptr);
        }
    }
}

void FrameBuffer::CreateFrameBuffer(std::vector<VkImageView>swapColorImagesViews,VkImageView depthImageView,VkRenderPass renderpass,VkExtent2D extent){
    m_framebuffer.resize(swapColorImagesViews.size());
    for(size_t i=0;i<swapColorImagesViews.size();++i){
        std::array<VkImageView,2>buffer_attachments={swapColorImagesViews[i],depthImageView};
        //what is this error???
        VkFramebufferCreateInfo framebufferInfo{};

        framebufferInfo.sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass=renderpass;
        framebufferInfo.attachmentCount=static_cast<uint32_t>(buffer_attachments.size());
        framebufferInfo.pAttachments=buffer_attachments.data();
        framebufferInfo.width=extent.width;
        framebufferInfo.height=extent.height;
        framebufferInfo.layers=1;

        if(vkCreateFramebuffer(m_device,&framebufferInfo,nullptr,&m_framebuffer[i])!=VK_SUCCESS){
            throw std::runtime_error("the framebuffer cannpt be formed");
        }

        
    }
}