#ifndef INDEX_BUFFER_CLASS
#define INDEX_BUFFER_CLASS

#include<vulkan/vulkan.h>
#include<vector>
#include<stdexcept>
#include<iostream>

class IndexBuffer{
    public:
    IndexBuffer(VkDevice device,VkPhysicalDevice physicalDevice,std::vector<uint32_t>& indices);
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&)=delete;
    IndexBuffer& operator=(const IndexBuffer&)=delete;
    
    VkBuffer getIndexBuffer(){return m_IndexBuffer;}
    VkDeviceMemory getDevicemem(){return m_deviceMemory;}


    private:

    VkBuffer m_IndexBuffer{VK_NULL_HANDLE};
    VkDeviceMemory m_deviceMemory{VK_NULL_HANDLE};
    VkDevice m_device{VK_NULL_HANDLE};
    VkDeviceSize m_indexCount{0};
    void uploadData(std::vector<uint32_t>& indices);
    uint32_t findMemory(uint32_t typefilter,VkMemoryPropertyFlags properties);
    void CreateIndexBuffer();
    VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};

};
#endif