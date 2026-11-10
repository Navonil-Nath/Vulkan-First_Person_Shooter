#include"Indexbuffer.hpp"

IndexBuffer::IndexBuffer(VkDevice device,VkPhysicalDevice physicalDevice,const std::vector<uint32_t>& indices):m_device(device),m_physicalDevice(physicalDevice){
    m_indexCount=indices.size();
    m_Index_ByteSize=static_cast<VkDeviceSize>(indices.size()*sizeof(uint32_t));
    if(m_indexCount==0){
        throw std::runtime_error("indices can't be empty");
    }
    CreateIndexBuffer();
    uploadData(indices);
}

IndexBuffer::~IndexBuffer(){
    if(m_IndexBuffer!=VK_NULL_HANDLE){
        vkDestroyBuffer(m_device,m_IndexBuffer,nullptr);
    }
    if(m_deviceMemory!=VK_NULL_HANDLE){
        vkFreeMemory(m_device,m_deviceMemory,nullptr);
    }
}

void IndexBuffer::uploadData(const std::vector<uint32_t>& indices){

    void* mappedMemory=nullptr;
    vkMapMemory(m_device,m_deviceMemory,0,m_Index_ByteSize,0,&mappedMemory);
    std::memcpy(mappedMemory,indices.data(),static_cast<size_t>(m_Index_ByteSize));
    vkUnmapMemory(m_device,m_deviceMemory);


}

uint32_t IndexBuffer::findMemory(uint32_t typefilter,VkMemoryPropertyFlags properties){

    VkPhysicalDeviceMemoryProperties m_properties{};
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice,&m_properties);

    for(uint32_t i=0;i<m_properties.memoryTypeCount;++i){
        bool ispresent=(typefilter & (1<<i));
        bool isSuitable=(properties & m_properties.memoryTypes[i].propertyFlags)==properties;

        if(ispresent && isSuitable){
            return i;
            
        }
    }
    throw std::runtime_error("failled to find the index buffer memeory");
}

void IndexBuffer::CreateIndexBuffer(){
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size=m_Index_ByteSize;
    bufferInfo.usage=VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    bufferInfo.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
    
    if(vkCreateBuffer(m_device,&bufferInfo,nullptr,& m_IndexBuffer)!=VK_SUCCESS){
        throw std::runtime_error("the index buffer for the custom objects coudn't be created");
    }

    VkMemoryRequirements memoryRequirements{};
    vkGetBufferMemoryRequirements(m_device,m_IndexBuffer,&memoryRequirements);

    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize=memoryRequirements.size;
    allocateInfo.memoryTypeIndex=findMemory(memoryRequirements.memoryTypeBits,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if(vkAllocateMemory(m_device,&allocateInfo,nullptr,&m_deviceMemory)!=VK_SUCCESS){
        throw std::runtime_error("coudn't allocate memeory for the verytex buffers");
    }

    vkBindBufferMemory(m_device,m_IndexBuffer,m_deviceMemory,0);

}
//was it recorded??


