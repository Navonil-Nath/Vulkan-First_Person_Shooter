#include"command.hpp"


CommandBuffer::CommandBuffer(VkDevice device,uint32_t queueIndex,uint32_t totalFrames):m_device(device),total_frames(totalFrames){
    CreateCommandpool(queueIndex);

}


CommandBuffer::~CommandBuffer(){
    if(m_commandPool!=VK_NULL_HANDLE){
        vkDestroyCommandPool(m_device,m_commandPool,nullptr); //if the pool is destroyed all the buffers formed from it is also destroyed
    }


}

void CommandBuffer::CreateCommandpool(uint32_t queueIndex){
    VkCommandPoolCreateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    createInfo.queueFamilyIndex=queueIndex;

    if(vkCreateCommandPool(m_device,&createInfo,nullptr,&m_commandPool)!=VK_SUCCESS){
        throw std::runtime_error("command pool cannot be created");
    }
}

//now these buffers are to be created seperatelly when needed
std::vector<VkCommandBuffer> CommandBuffer::allocateCommandBuffers(uint32_t totalFrames){
    std::vector<VkCommandBuffer>commandBuffers(totalFrames);

    VkCommandBufferAllocateInfo allocateInfo{};

    allocateInfo.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.commandPool=m_commandPool;
    allocateInfo.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY; //means these buffers can be directlly submitted to the queue forbeing read by the GPU
    allocateInfo.commandBufferCount=totalFrames;
    

    if(vkAllocateCommandBuffers(m_device,&allocateInfo,commandBuffers.data())!=VK_SUCCESS){
        throw std::runtime_error("the command buffers for the per frame  coudn't be formed");
    };
    return commandBuffers;
}

//now we will make function for creating custom command buffers for special purposes
//this function will return only a single command buffer for a single time use

VkCommandBuffer CommandBuffer::beginSingleTimeCommand(){
    VkCommandBufferAllocateInfo createInfo{};
    createInfo.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    createInfo.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    createInfo.commandPool=m_commandPool;
    createInfo.commandBufferCount=1;
    
    VkCommandBuffer Command_Buffer{VK_NULL_HANDLE};

    VkCommandBufferBeginInfo allocate_createInfo{};
    //this will prepare the returned buffer by this function writable by the cpu
    allocate_createInfo.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    allocate_createInfo.pNext=nullptr;
    allocate_createInfo.flags=VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    allocate_createInfo.pInheritanceInfo=nullptr; //why showing errro??

    vkBeginCommandBuffer(Command_Buffer,&allocate_createInfo);

    return Command_Buffer;
}

//now we will write the functions which will pause writing on the buffer and submit it to the queue to be takes by the 
//gpu later

void CommandBuffer::endSingleTimeCommandBuffer(VkQueue queue,VkCommandBuffer commandBuffer){
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount=1;
    submitInfo.pCommandBuffers=&commandBuffer;
    
    //prepare the queue 

    vkQueueSubmit(queue,1,&submitInfo,VK_NULL_HANDLE);
    vkFreeCommandBuffers(m_device,m_commandPool,1,&commandBuffer);



}

