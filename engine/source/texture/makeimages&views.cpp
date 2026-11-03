#include"makeimages&views.hpp"



//now we will write the image barrier and trandition and copy functions for transfering the texture form the cpu side to the gpu
//vram side into the memeory block pointed to by the vkimage


//this function below has to be called seperately at the time of the pixels transfer for each image
void CreateImage::UploadFromBuffer(VkImage image,CommandBuffer& bufferHandle,VkQueue queue,VkBuffer staggingBuffer,Texture_Image& image_Object){
    //prepare the image barrier and the memeory block on the gpu to receive the pixel data
    TransitionLayout(image,bufferHandle,queue,VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferData(image,bufferHandle,queue,staggingBuffer,image_Object);
    //after the transfer is done change the imagetype to shader read only
    TransitionLayout(image,bufferHandle,queue,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void CreateImage::TransitionLayout(VkImage image,CommandBuffer& bufferHandle,VkQueue queue,VkImageLayout oldLayout,VkImageLayout newLayout){

    VkCommandBuffer cmd=bufferHandle.beginSingleTimeCommand();
    VkImageMemoryBarrier Barrier{}; //this is required beacuse gpu acts asynchronouslly and the transfer from the one layout to the other for a memeory block on the gpu takes time 
    Barrier.sType=VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    Barrier.oldLayout=oldLayout;
    Barrier.newLayout=newLayout;
    Barrier.srcQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED;
    Barrier.dstQueueFamilyIndex=VK_QUEUE_FAMILY_IGNORED;
    Barrier.image=image;
    Barrier.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
    Barrier.subresourceRange.baseMipLevel=0;
    Barrier.subresourceRange.levelCount=1;
    Barrier.subresourceRange.baseArrayLayer=0;
    Barrier.subresourceRange.layerCount=1;


    //now to initiate the VkPipelinestageFlags structs -->they tell the vulkan when to put the VkImageMemoryBarrier
    //at appropiate places of the memeory transition points

    VkPipelineStageFlags sourceStage{};
    VkPipelineStageFlags dstStage{};


    if(oldLayout==VK_IMAGE_LAYOUT_UNDEFINED && newLayout==VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL){
        Barrier.srcAccessMask=0; //the memory is intiallyempty
        Barrier.dstAccessMask=VK_ACCESS_TRANSFER_WRITE_BIT; //telling the gpu that the memeory will now receive data
        sourceStage=VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        dstStage=VK_PIPELINE_STAGE_TRANSFER_BIT;


    }
    else if(oldLayout==VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout==VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL){
        Barrier.srcAccessMask=VK_ACCESS_TRANSFER_WRITE_BIT;
        Barrier.dstAccessMask=VK_ACCESS_SHADER_WRITE_BIT;
        sourceStage=VK_PIPELINE_STAGE_TRANSFER_BIT;
        dstStage=VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT; //telling the gpu that the memeory will now to be read by the fragment shader


    }
    else{
        throw std::runtime_error("the memeory block layouts change operation coudn't be perfomed");
    }

    vkCmdPipelineBarrier( //recording this to the command buffer ,after this the gpu knows when to stop other commands from execution during the memeory phase chage
        cmd,
        sourceStage,
        dstStage,
        0,
        0,
        nullptr,
        0,
        nullptr,
        1,
        &Barrier
    );
    bufferHandle.endSingleTimeCommandBuffer(queue,cmd);

}

void CreateImage::copyBufferData(VkImage image,CommandBuffer& bufferHandle,VkQueue queue,VkBuffer staggingBuffer,Texture_Image& image_Object){

    //now to actiually move the data to the gpu memeory(vram)
    VkCommandBuffer cmd=bufferHandle.beginSingleTimeCommand();
    VkBufferImageCopy copyregion{};
    copyregion.bufferOffset=0; //start from the very start of the VkBuffer from where the data is to be copied
    copyregion.bufferRowLength=0;
    copyregion.bufferImageHeight=0; //VkBuffer is a 1D image
    copyregion.imageSubresource.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT; //for the albedo image only
    copyregion.imageSubresource.mipLevel=0;
    copyregion.imageSubresource.baseArrayLayer=0;
    copyregion.imageSubresource.layerCount=1;
    copyregion.imageOffset={0,0,0}; //start writting from the very beginig of the vkimage
    copyregion.imageExtent={image_Object.m_texture_width,image_Object.m_texture_height};

    //now write the copy operation to the comand buffer for it to be later executed by the gpu when submitted to the queue
    vkCmdCopyBufferToImage(
        cmd,
        staggingBuffer,
        image_Object.m_image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &copyregion
    );

    bufferHandle.endSingleTimeCommandBuffer(queue,cmd);


}