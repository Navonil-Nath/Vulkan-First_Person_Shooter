/*

                                        Theory
we will now create the command buffers and command pool.command buffers are the one where the cpu writes commands for the gpu to execute
first the cpu asks for the buffer corresponding to that frame.the VkFence is the one which flags whether the buffer corresponding to that frame
is available or not.if the buffer is currentlly being read by the gpu then it is not else the VkFence made it available to the 
cpu to write on it.now  if available the cpu writes on it then sends it to the queue.we will write a command which  will prepare
a command buffer and then take the input from use and then submit it to the queue.

the synchronisation part consists of the semaphores and the fence
each frame shall contain these-->one VkSemaphore for guarding whether a image is available for rendering by the gpu or not
another VkSemaphore fpr guarding whether the gpu has finished rendering onto a VkImage of the current frame or not beacuse remeber gpu works asynchronouslly within itself
it can very much happen that the gpu starts rendering onto a different frame without completing rendering onto the current frame 
just beacuse the cpu has submitted another command buffer  with new tasks, now the cpu side too requires a guardian beacuse cpu and gpu too works asynchronouslly 
wrt to each other, for this case the VkFence comes into the picture it watches over whether the gpu has currentlly finished rendering onto the current frame 
and if yes then only provides it with another command buffer from the VkQueue

One more thing from a command pool command buffers are formed.


*/

#ifndef VK_COMMAND_BUFFER
#define VK_COMMAND_BUFFER
#include<stdexcept>
#include<iostream>
#include<vulkan/vulkan.h>
#include<vector>

class CommandBuffer{

    public:
        CommandBuffer(VkDevice device,uint32_t queueIndex,uint32_t totalFrames);
        ~CommandBuffer();

        CommandBuffer(const CommandBuffer&)=delete;
        CommandBuffer& operator=(const CommandBuffer&)=delete;

        VkCommandPool get(){return m_commandPool;}
        std::vector<VkCommandBuffer> allocateCommandBuffers(uint32_t totalFrames);//--call the buffers---

        VkCommandBuffer beginSingleTimeCommand(); //this returns a command buffer which can be used to write various gpu related actionslike copying data from stagging buffer to VRAM
        void endSingleTimeCommandBuffer(VkQueue queue,VkCommandBuffer commandBuffer);

    private:

        VkCommandPool m_commandPool{VK_NULL_HANDLE};
        uint32_t total_frames=0;
        uint32_t QueueIndex=0;
        void CreateCommandpool(uint32_t queueIndex);
        VkDevice m_device{VK_NULL_HANDLE};

    

};

#endif