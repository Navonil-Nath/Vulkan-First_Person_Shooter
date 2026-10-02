#include"sync.hpp"

SyncObjects::SyncObjects(int maxFrames,VkDevice device):m_device(m_device){
    CreateSyncObject(maxFrames);
}


SyncObjects::~SyncObjects(){
    for(size_t i= 0;i<m_imageAvailableSemaphore.size();++i){
        if(m_imageAvailableSemaphore[i]!=VK_NULL_HANDLE){
            vkDestroySemaphore(m_device,m_imageAvailableSemaphore[i],nullptr);
        }
        if(m_imagefinishedRenderingSemaphore[i]!=VK_NULL_HANDLE){
            vkDestroySemaphore(m_device,m_imagefinishedRenderingSemaphore[i],nullptr);
        }
        if(m_cpugpufence[i]!=VK_NULL_HANDLE){
            vkDestroyFence(m_device,m_cpugpufence[i],nullptr);
        }

    }
    
}

void SyncObjects::CreateSyncObject(int maxFrames){
    m_imageAvailableSemaphore.resize(maxFrames);
    m_imagefinishedRenderingSemaphore.resize(maxFrames);
    m_cpugpufence.resize(maxFrames);

    VkSemaphoreCreateInfo semaphoreCreateInfo{};
    semaphoreCreateInfo.sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags=VK_FENCE_CREATE_SIGNALED_BIT;

    for(size_t i=0;i<maxFrames;++i){
        if(!vkCreateSemaphore(m_device,&semaphoreCreateInfo,nullptr,&m_imageAvailableSemaphore[i]) || !vkCreateSemaphore(m_device,&semaphoreCreateInfo,nullptr,&m_imagefinishedRenderingSemaphore[i]) || !vkCreateFence(m_device,&fenceInfo,nullptr,&m_cpugpufence[i])){
            throw std::runtime_error("failled to initilase the semaphores and the fences");
        }
    }

}