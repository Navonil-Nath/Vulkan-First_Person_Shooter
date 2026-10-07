#ifndef STAGGING_BUFFER_CLASSS
#define STAGGING_BUFFER_CLASS
#include<iostream>
#include<vulkan/vulkan.h>
/*
this step will be used as a intermidiatery step for uploading data to the gpu sidefrom the cpu
after that using the gpu we will copy that data from this stagging buffer side of the gpu to the 
VRAM using command buffers

this step is required for uploading every model we want to render in the scene
*/

class StaggingBuffer{
    public:
        StaggingBuffer(VkDevice device,VkPhysicalDevice physicalDevice,void* data,VkDeviceSize size);
        ~StaggingBuffer();

        StaggingBuffer(const StaggingBuffer&)=delete;
        StaggingBuffer& operator=(const StaggingBuffer&)=delete;

        VkDeviceSize getDeviceSize(){return m_stagingmemeorySize;}

        VkBuffer getBuffer(){return m_staggingBuffer;}
        
    private:
        VkDevice m_device{VK_NULL_HANDLE};
        VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
        VkBuffer m_staggingBuffer;
        VkDeviceMemory m_staggingmemeory{VK_NULL_HANDLE}; //the memory on the gpu where the m_staggingBuffer will be pointing to..
        VkDeviceSize m_stagingmemeorySize{0};

        void CreateBuffer();
        uint32_t findMemoryIndex(uint32_t typeFilter,VkMemoryPropertyFlags properties);

        void uploadData(void* data);


};

#endif