#include"Stagingbuffer.hpp"
#include<stdexcept>
#include<cstdlib>


StaggingBuffer::StaggingBuffer(VkDevice device,VkPhysicalDevice physicalDevice,void* data,VkDeviceSize size):m_device(device),m_physicalDevice(physicalDevice),m_stagingmemeorySize(size){
    if(data==nullptr){
        throw std::runtime_error("the data to be filled in the gpy stagging buffer cannot be null");
    }
   
    CreateBuffer();
    uploadData(data);
    
}

StaggingBuffer::~StaggingBuffer(){
    if(m_staggingBuffer!=VK_NULL_HANDLE){
        vkDestroyBuffer(m_device,m_staggingBuffer,nullptr);
    }
    if(m_staggingmemeory!=VK_NULL_HANDLE){
        vkFreeMemory(m_device,m_staggingmemeory,nullptr);
    }
}

uint32_t StaggingBuffer::findMemoryIndex(uint32_t typeFilter,VkMemoryPropertyFlags properties){
    //now we have the memories which are compatibel but now we need to get their indices in the device
    VkPhysicalDeviceMemoryProperties memoryProperties{};
    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice,&memoryProperties);

    for(uint32_t i=0;i<memoryProperties.memoryTypeCount;++i){
        bool typeMatches = typeFilter & (1<<i);
        bool prop_available=(memoryProperties.memoryTypes[i].propertyFlags==properties);
        if(typeMatches && prop_available){
            return i;
        }
    }

    throw std::runtime_error("no suitable memeory found");

}

void StaggingBuffer::uploadData(void* data){
    //now after memory allocation in the gou and binding it with the buffer is done 
// we need to upload data from the cpu to that memory

void* mappedMemory=nullptr; //this will be  the pointer to the gpu's stagging bufer memory
//mapping it to the gpu's m_staggingmemeory
vkMapMemory(m_device,m_staggingmemeory,0,m_stagingmemeorySize,0,&mappedMemory);

//after mapping whatever data is poured to the mappedmemory on the cpu side
//will get transfered to the gpu's stagig buffer side using memcpy
std::memcpy(mappedMemory,data,static_cast<size_t>(m_stagingmemeorySize));

//now unmap it for safety
vkUnmapMemory(m_device,m_staggingmemeory);

}

void StaggingBuffer::CreateBuffer(){
    //here it will create and bind the buffer to the appropiate memeory slot on the gpu's cpu visible memeory area
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size=m_stagingmemeorySize;
    bufferInfo.usage=VK_BUFFER_USAGE_TRANSFER_SRC_BIT; //beacuse the buffer will receive data
    bufferInfo.sharingMode=VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(m_device,&bufferInfo,nullptr,&m_staggingBuffer)!=VK_SUCCESS){
        throw std::runtime_error("the stagging buffer coudn't be created");
    }

    //now get the memeory requirements on the gpu's stagging stage for storing all the data represented by the stagging buffer to the 
    //stagging stage of the gpu memeory

    VkMemoryRequirements requirements{};
    vkGetBufferMemoryRequirements(m_device,m_staggingBuffer,nullptr);

    //now check if memeory is available
    if(requirements.size==0){
        throw std::runtime_error("the memeory isn't availabel");
    }

    //else allocate the memory from the gpu
    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize=requirements.size;
    allocateInfo.memoryTypeIndex=findMemoryIndex(requirements.memoryTypeBits,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);


    if(vkAllocateMemory(m_device,&allocateInfo,nullptr,&m_staggingmemeory)!=VK_SUCCESS){
        throw std::runtime_error("failled to allocate the staging memory on the gpu");
    }

    //bind the memeory with the m_staggingBuffer
    vkBindBufferMemory(m_device,m_staggingBuffer,m_staggingmemeory,0);

}



