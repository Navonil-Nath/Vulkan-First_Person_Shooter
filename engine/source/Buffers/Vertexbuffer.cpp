#include"VertexBuffer.hpp"
#include<stdexcept>

VertexBuffer::VertexBuffer(VkPhysicalDevice physicalDevice,VkDevice device,std::vector<Vertex>& vertices):m_device(device),m_physicalDevice(physicalDevice)
{
    m_size=static_cast<uint64_t>(vertices.size());
    if(m_size==0){
        throw std::runtime_error("failled to fecth vertices");
    }    
    CreateBuffer();
    uploadBuffer(vertices);
}
VertexBuffer::~VertexBuffer(){
    if(m_vertexBuffer!=VK_NULL_HANDLE){
        vkDestroyBuffer(m_device,m_vertexBuffer,nullptr);
    }
    if( m_deviceMemory!=VK_NULL_HANDLE){
        vkFreeMemory(m_device, m_deviceMemory,nullptr);
    }
}

void VertexBuffer::uploadBuffer(std::vector<Vertex>& vertices){

    void*mappedMemory=nullptr;
    vkMapMemory(m_device,m_deviceMemory,0,m_size,0,&mappedMemory);
    std::memcpy(mappedMemory,vertices.data(),static_cast<uint32_t>(m_size));
    vkUnmapMemory(m_device,m_deviceMemory);

}

uint32_t VertexBuffer::findMemory(uint32_t typeFilter,VkMemoryPropertyFlags properties){
    VkPhysicalDeviceMemoryProperties memoryProperties{};
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice,&memoryProperties);
    for(uint32_t i=0;i<memoryProperties.memoryTypeCount;++i){
        bool typeMatch=(typeFilter & (1<<i));
        bool flagsMatch=(properties & memoryProperties.memoryTypes[i].propertyFlags)==properties;

        if(flagsMatch && typeMatch){
            return i;
        }
    }

    throw std::runtime_error("coudn't find the appropiate memory");

}


void VertexBuffer::CreateBuffer(){
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size=m_size;
    bufferInfo.usage=VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
    
    
    if(vkCreateBuffer(m_device,&bufferInfo,nullptr,& m_vertexBuffer)!=VK_SUCCESS){
        throw std::runtime_error("thevertex buffer for the custom objects coudn't be created");
    }

    VkMemoryRequirements memoryRequirements{};
    vkGetBufferMemoryRequirements(m_device,m_vertexBuffer,&memoryRequirements);


    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize=m_size;
    allocateInfo.memoryTypeIndex=findMemory(memoryRequirements.memoryTypeBits,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if(vkAllocateMemory(m_device,&allocateInfo,nullptr,&m_deviceMemory)!=VK_SUCCESS){
        throw std::runtime_error("coudn't allocate memeory for the verytex buffers");
    }

    vkBindBufferMemory(m_device,m_vertexBuffer,m_deviceMemory,0);

}
