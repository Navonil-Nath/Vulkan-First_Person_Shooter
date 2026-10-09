#include"UniformBuffer.hpp"

UniformBuffer::UniformBuffer(VkDevice device,VkPhysicalDevice physicalDevice):m_device(device),m_physicalDevice(physicalDevice){
    CreateBuffer();
}

UniformBuffer::~UniformBuffer(){
    if(m_buffer!=VK_NULL_HANDLE){
        vkDestroyBuffer(m_device,m_buffer,nullptr);
    }
    if(m_memory!=VK_NULL_HANDLE){
        vkFreeMemory(m_device,m_memory,nullptr);
    }
}

void UniformBuffer::CreateBuffer(){
    VkBufferCreateInfo uboBufferInfo{};
    uboBufferInfo.sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    uboBufferInfo.size=sizeof(UniformBufferObject);
    uboBufferInfo.usage=VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    uboBufferInfo.sharingMode=VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(m_device,&uboBufferInfo,nullptr,&m_buffer)!=VK_SUCCESS){
        throw std::runtime_error("the ubo buffer coudn't be formed");
    }

    VkMemoryRequirements memoryRequirement{};
    vkGetBufferMemoryRequirements(m_device,m_buffer,&memoryRequirement);

    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize=memoryRequirement.size;
    allocateInfo.memoryTypeIndex=findMemory(memoryRequirement.memoryTypeBits,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if(vkAllocateMemory(m_device,&allocateInfo,nullptr,&m_memory)!=VK_SUCCESS){
        throw std::runtime_error("memory allocation for the ubo failled");
    }

}

uint32_t UniformBuffer::findMemory(uint32_t typeFilter,VkMemoryPropertyFlags flags){
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice,&memoryProperties);


    for(uint32_t i=0;i<memoryProperties.memoryTypeCount;++i){
        bool typeMatches=typeFilter & (1<<i);
        bool flagsMatch=(memoryProperties.memoryTypes[i].propertyFlags & flags)==flags;
        if(typeMatches && flagsMatch){
            return i;

        }
    }

    throw std::runtime_error("no suitable memeory found for the ubo");

}

void UniformBuffer::Upload(UniformBufferObject& object){
    void* memory=nullptr;
    vkMapMemory(m_device,m_memory,0,sizeof(object),0,&memory);
    std::memcpy(memory,&object,sizeof(object));
    vkUnmapMemory(m_device,m_memory);    

}