#ifndef SYNC_OBJECTS_CLASS
#define SYNC_OBJECTS_CLASS

#include<vulkan/vulkan.h>
#include<iostream>
#include<cstdlib>
#include<stdexcept>
#include<vector>

class SyncObjects{
    public:
        SyncObjects(int maxFrames,VkDevice device);
        ~SyncObjects();

        SyncObjects(const SyncObjects&)=delete;
        SyncObjects& operator=(const SyncObjects&)=delete;

        VkSemaphore getImageAvailableSemaphore(int i) {return m_imageAvailableSemaphore[i];}
        VkSemaphore getImageRenderedFinishedSemaphore(int i){return m_imagefinishedRenderingSemaphore[i];}
        VkFence getcpuGpuFence(int i){return m_cpugpufence[i];}


    private:
        std::vector<VkSemaphore> m_imageAvailableSemaphore;
        std::vector<VkSemaphore>m_imagefinishedRenderingSemaphore;
        std::vector<VkFence>m_cpugpufence;

        void CreateSyncObject(int maxFrames);
        VkDevice m_device{VK_NULL_HANDLE};


};

#endif