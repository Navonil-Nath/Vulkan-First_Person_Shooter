#ifndef VERTEX_BUFFER_CLASS
#define VERTEX_BUFFER_CLASS


/*
here we will implement that systeam which will take in the vector of the 3d models vertices and upload them to the stagging buffer

now a quick note:the stagingbuffer class i created earlier was for the models loaded using gltf or extrenal 3dmodels or cubemaps and textures
that will be required to be transfereed to the VRAM from the stagging buffer

the vertexBuffer is for the transferring our cubes or speheres data to the stagging buffer
whose vertices we will define here ourselves
*/

#include<iostream>
#include<stdexcept>
#include<stdexcept>
#include<vulkan/vulkan.h>
#include"vertex.hpp"
#include<vector>


class VertexBuffer{
    public:
    VertexBuffer(VkPhysicalDevice physicalDevice,VkDevice device,std::vector<Vertex>& vertices);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&)=delete;
    VertexBuffer& operator=(const VertexBuffer&)=delete;
    

    VkBuffer getVertexBuffer(){return m_vertexBuffer;}
    VkDeviceMemory getVertexmemory(){return m_deviceMemory;}


    private:
    uint32_t findMemory(uint32_t typeFilter,VkMemoryPropertyFlags properties);
    void CreateBuffer();
    void uploadBuffer(std::vector<Vertex>& vertices);

    VkBuffer m_vertexBuffer{VK_NULL_HANDLE};
    VkDevice m_device{VK_NULL_HANDLE};
    VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
    VkDeviceSize m_size{0};
    VkDeviceMemory m_deviceMemory{VK_NULL_HANDLE};


};

#endif