#include"app.hpp"
#include<iostream>
#include<memory>
#include<GLFW/glfw3.h>
#include<string>

void App::UpdateUniformBuffer(float deltaTime){
    m_camera->ProcessInput(m_glfw_window.get(),deltaTime);
    VkExtent2D extent=m_swapchain->getExtent();
    float aspectRatio=static_cast<float>(extent.width)/static_cast<float>(extent.height);
    UniformBufferObject ubo{};
    ubo.view=m_camera->getViewMatrice();
    ubo.projection=m_camera->getProjectionMatrice(aspectRatio);
    ubo.MainCameraSpace=ubo.projection*ubo.view; //here the order is ext importent as we first perform view then projection for each of the vertices

    m_uniform_buffer->Upload(ubo);

}

void App::RecordCommandBuffer(VkCommandBuffer buffer,uint32_t imageIndex){

//all these below will go into a single command buffer for one complete frame    

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if(vkBeginCommandBuffer(buffer,&beginInfo)!=VK_SUCCESS){
        throw std::runtime_error("unable to start recording on the swapchin related command buffers");
    }

    std::array<VkClearValue,2>imageClearValues{};
    imageClearValues[0].color={{0.04f,0.03f,0.02f,1.0f}};  //color image of the framebuffer
    imageClearValues[1].depthStencil={1.0f,0};             //depth image of the framebuffer
     
    //recording the commands to begin renderpass operations
    VkRenderPassBeginInfo renderInfo{};
    renderInfo.sType=VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderInfo.renderPass=m_renderPass->get();
    renderInfo.framebuffer=m_frambuffer_handle->get()[imageIndex];
    renderInfo.renderArea.offset={0,0};
    renderInfo.renderArea.extent=m_swapchain->getExtent();
    renderInfo.clearValueCount=static_cast<uint32_t>(imageClearValues.size());
    renderInfo.pClearValues=imageClearValues.data();

    vkCmdBeginRenderPass(buffer,&renderInfo,VK_SUBPASS_CONTENTS_INLINE);

    //binding these below descriptor sets
    std::array<VkDescriptorSet,3>descriptorSets={
        cube_descriptor_set->get(),uniform_buffer_set->get(),skybox_descriptor_set->get()
    };
    //binding the escriptor sets
    vkCmdBindDescriptorSets(buffer,VK_PIPELINE_BIND_POINT_GRAPHICS,m_pipeline_layout->get(),0,static_cast<uint32_t>(descriptorSets.size()),descriptorSets.data(),0,nullptr);

    //bind the push constants to the gpu registers
    pushConstant.model={1.0f};  //meaning the models will be loaded at the 0,0,0
    vkCmdPushConstants(buffer,m_pipeline_layout->get(),VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,0,sizeof(PushConstantObject),&pushConstant);
    //binding the index and vertex buffers
    VkBuffer vertexBuffer[]={m_cube_Vertex_Buffer->getVertexBuffer()};
    vkCmdBindVertexBuffers(buffer,0,1,vertexBuffer,{0});
    vkCmdBindIndexBuffer(buffer,m_cube_Index_Buffer->getIndexBuffer(),0,VK_INDEX_TYPE_UINT32);


    //binding the pipelines
    //bind the cube pipeline and ask the gpu to draw it
    vkCmdBindPipeline(buffer,VK_PIPELINE_BIND_POINT_GRAPHICS,cube_pipeline->get());
    vkCmdDrawIndexed(buffer,m_cube_Index_Buffer->getIndex_Count(),1,0,0,0);


    //bind the skybox pipleine and draw it
    vkCmdBindPipeline(buffer,VK_PIPELINE_BIND_POINT_GRAPHICS,skybox_pipeline->get());
    vkCmdDrawIndexed(buffer,m_cube_Index_Buffer->getIndex_Count(),1,0,0,0);

    vkCmdEndRenderPass(buffer);

    vkEndCommandBuffer(buffer); //we can alos use the stdexcept here

}

void App::DrawFrame(){
    VkFence inFlightFence=m_sync_objects->getcpuGpuFence(current_frame);
    vkWaitForFences(m_logical_device->get(),1,&inFlightFence,VK_TRUE,UINT64_MAX);
    vkResetFences(m_logical_device->get(),1,&inFlightFence);

    uint32_t imageIndex=0;
    vkAcquireNextImageKHR(m_logical_device->get(),m_swapchain->get(),UINT64_MAX,m_sync_objects->getImageAvailableSemaphore(current_frame),VK_NULL_HANDLE,&imageIndex); //acquire the availabe swapchain image]
    vkResetCommandBuffer(m_command_handle->getBuffer()[current_frame],0);

    RecordCommandBuffer(m_command_handle->getBuffer()[current_frame],imageIndex);


    //now after recording on the beffer we will need to send this to the queue submit
    //after aubmiting to the gpu
    //for that we need to synchronise the gpu taskflow directing the gpu when to render as when image is available to when presentation engine
    //rendering it to the screen to obtain the image back
    VkSemaphore waitSemaphores[]={m_sync_objects->getImageAvailableSemaphore(current_frame)}; //this semaphore flags ok if the image is finished rendering of the current frame
    VkPipelineStageFlags waitStages[]={VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT}; //meaning the gou must finish any fragment shader's color writting before any other taks to proceed
    VkSemaphore signalSemaphore[]={m_sync_objects->getImageRenderedFinishedSemaphore(current_frame)}; //this signals the cpu that the gpu has finished rendering onto this image 

    VkSubmitInfo submitInfo{};
    submitInfo.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount= 1;
    submitInfo.pWaitSemaphores=waitSemaphores;
    submitInfo.pWaitDstStageMask=waitStages;
    submitInfo.commandBufferCount=1;
    submitInfo.pCommandBuffers=&m_command_handle->getBuffer()[current_frame];
    submitInfo.signalSemaphoreCount=1;
    submitInfo.pSignalSemaphores=signalSemaphore;

    if(vkQueueSubmit(m_logical_device->getQueue(),1,&submitInfo,inFlightFence)!=VK_SUCCESS){
        throw std::runtime_error("the buffer coudn't be submitted to the queue");
    }

    //from the queue after proceesing by gpu then to the presentation engine
    VkSwapchainKHR swapchain[]={m_swapchain->get()};

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount=1;
    presentInfo.pWaitSemaphores=signalSemaphore;
    presentInfo.swapchainCount=1;
    presentInfo.pSwapchains=swapchain;
    presentInfo.pImageIndices=&imageIndex;

    vkQueuePresentKHR(m_logical_device->getQueue(),&presentInfo);


    //updating the frame no
    current_frame=(current_frame+1)%MAX_FRAMES_IN_FLIGHT;

}




App::App(){
    m_vulkan_instance=std::make_unique<VulkanInstance>("Kitten_Engine");
    m_window_surface=std::make_unique<WindowSurface>(m_glfw_window.get(),m_vulkan_instance->get());
    m_physical_Device=std::make_unique<PhysicalDevice>(m_vulkan_instance->get(),m_window_surface->get());
    m_logical_device=std::make_unique<LogicalDevice>(m_physical_Device->get(),m_window_surface->get());
    m_swapchain=std::make_unique<Swapchain>(m_logical_device->get(),m_physical_Device->get(),m_window_surface->get(),m_glfw_window.get());
    m_swapchainImageView=std::make_unique<SwapchainImageView>(m_logical_device->get(),m_swapchain->get(),m_swapchain->getFormat());
    m_depthResource=std::make_unique<DepthResource>(m_physical_Device->get(),m_logical_device->get(),m_swapchain->getExtent(),VK_FORMAT_D32_SFLOAT);
    //m_depthResource contains the both view and image(above)
    m_renderPass=std::make_unique<RenderPass>(m_swapchain->getFormat(),m_depthResource->getFormat(),m_logical_device->get());
    m_frambuffer_handle=std::make_unique<FrameBuffer>(m_logical_device->get(),m_swapchainImageView->get(),m_depthResource->getImageView(),m_renderPass->get(),m_swapchain->getExtent());
    m_command_handle=std::make_unique<CommandBuffer>(m_logical_device->get(),m_logical_device->getQueueIndex(),MAX_FRAMES_IN_FLIGHT);
    m_sync_objects=std::make_unique<SyncObjects>(MAX_FRAMES_IN_FLIGHT,m_logical_device->get());
    m_Descriptor_Pool=std::make_unique<DescriptorPool>(m_logical_device->get());
    m_texture_sampler=std::make_unique<TextureSampler>(m_logical_device->get(),Sampler::Repeat);
    m_uniform_buffer=std::make_unique<UniformBuffer>(m_logical_device->get(),m_physical_Device->get());
    m_image_and_view_maker=std::make_unique<CreateImage>(); //to be used each time tansition operations to be done on the memory
    m_camera=std::make_unique<Camera>(glm::vec3{0.0f,0.0f,3.0f});  //so that the cubes doesn't render covering the camera
    //--------------cube-------------------------------
   
    m_cube_Vertex_Buffer=std::make_unique<VertexBuffer>(m_physical_Device->get(),m_logical_device->get(),CubeMeshData::getCubeVertices());
    m_cube_Index_Buffer=std::make_unique<IndexBuffer>(m_logical_device->get(),m_physical_Device->get(),CubeMeshData::getIndices());
    
    //forming the imageviews and putting data in memeory
    for(const std::string& path: cubeTexturesPath){
        LoadedImage rawImage=ImageLoader::loadTexture(path);
        VkDeviceSize imageSize=static_cast<VkDeviceSize>(rawImage.width*rawImage.height*4);

        //now we need to copy this image to the stagging buffer
        StaggingBuffer stagging_buffer(m_logical_device->get(),m_physical_Device->get(),rawImage.pixels,imageSize);

        std::unique_ptr<Texture_Image> texture=std::make_unique<Texture_Image>(m_logical_device->get(),m_physical_Device->get(),static_cast<uint32_t>(rawImage.width),static_cast<uint32_t>(rawImage.height),VK_FORMAT_R8G8B8A8_SRGB);

        m_image_and_view_maker->UploadFromBuffer(texture->get_image(),*m_command_handle,m_logical_device->getQueue(),stagging_buffer.getBuffer(),*texture);
        m_cube_textures_imageViews.push_back(texture->get_image_view());

        m_cube_textures.push_back(std::move(texture));
        
    }
    
    //now form the descriptor sets

    std::vector<VkDescriptorSetLayoutBinding>m_cube_descriptor_layout_Bindings;
    m_cube_descriptor_layout_Bindings.resize(1);
    m_cube_descriptor_layout_Bindings[0].binding=0;
    m_cube_descriptor_layout_Bindings[0].descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    m_cube_descriptor_layout_Bindings[0].descriptorCount=6;
    m_cube_descriptor_layout_Bindings[0].stageFlags=VK_SHADER_STAGE_FRAGMENT_BIT;
    m_cube_descriptor_layout_Bindings[0].pImmutableSamplers=nullptr;
    

    cube_texture_layout=std::make_unique<DescriptorSetLayout>(m_logical_device->get(),m_cube_descriptor_layout_Bindings);
    cube_descriptor_set=std::make_unique<DescriptorSet>(m_logical_device->get(),cube_texture_layout->get(),m_Descriptor_Pool->get());
    //now fill the set wtih the descriptors
    m_cube_texture_descriptor=std::make_unique<cubeTextureDescriptor>();

    m_cube_texture_descriptor->createTextureDescriptor(m_logical_device->get(),cube_descriptor_set->get(),m_texture_sampler->get(),m_cube_textures_imageViews);

    activeLayouts.push_back(cube_texture_layout->get());

    //----------------------cube---------------------------
    //---------uniformBufferDescriptor---------------------

    uniform_buffer_bindings.resize(1);
    uniform_buffer_bindings[0].binding=0;
    uniform_buffer_bindings[0].descriptorType=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uniform_buffer_bindings[0].descriptorCount=1;
    uniform_buffer_bindings[0].stageFlags=VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    uniform_buffer_bindings[0].pImmutableSamplers=nullptr;

    uniform_descriptor_set_layout=std::make_unique<DescriptorSetLayout>(m_logical_device->get(),uniform_buffer_bindings);
    uniform_buffer_set=std::make_unique<DescriptorSet>(m_logical_device->get(),uniform_descriptor_set_layout->get(),m_Descriptor_Pool->get());

    //fill the set with the descriptors
    uniform_descriptor_creator=std::make_unique<UniformBufferDescriptor>();
    uniform_descriptor_creator->CreateUniformBufferDescriptor(m_logical_device->get(),uniform_buffer_set->get(),m_uniform_buffer->get());
    activeLayouts.push_back(uniform_descriptor_set_layout->get());

    //--------------uniformBufferDescriptor---------------------------------------

    //------skybox descriptor set creating-----------------------
    
     skybox_texture_sampler=std::make_unique<TextureSampler>(m_logical_device->get(),Sampler::ClampToEdge);

     for(const std::string& path: skyBoxTexturePath){
        LoadedImage rawImage=ImageLoader::loadTexture(path);
        VkDeviceSize size=static_cast<VkDeviceSize>(rawImage.width*rawImage.height*4);  //since stb_image gives four floats per pixel
        StaggingBuffer m_staggingBuffer(m_logical_device->get(),m_physical_Device->get(),rawImage.pixels,size);
        std::unique_ptr<Texture_Image> texture=std::make_unique<Texture_Image>(m_logical_device->get(),m_physical_Device->get(),static_cast<uint32_t>(rawImage.width),static_cast<uint32_t>(rawImage.height),VK_FORMAT_R8G8B8A8_SRGB);
        m_image_and_view_maker->UploadFromBuffer(texture->get_image(),*m_command_handle,m_logical_device->getQueue(),m_staggingBuffer.getBuffer(),*texture);
        skybox_texture_image_views.push_back(texture->get_image_view());
        skybox_texture_images.push_back(texture);
    }


    skybox_layout_bindings.resize(1); //single binding will hold 6 descriptors ,each descriptor holding the VkImageView of each texture image
    skybox_layout_bindings[0].binding=0;
    skybox_layout_bindings[0].descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    skybox_layout_bindings[0].descriptorCount=6;
    skybox_layout_bindings[0].stageFlags=VK_SHADER_STAGE_FRAGMENT_BIT;
    skybox_layout_bindings[0].pImmutableSamplers=nullptr;


    skybox_descriptorSet_layout=std::make_unique<DescriptorSetLayout>(m_logical_device->get(),skybox_layout_bindings);
    skybox_descriptor_set=std::make_unique<DescriptorSet>(m_logical_device->get(),skybox_descriptorSet_layout->get(),m_Descriptor_Pool->get());

    skybox_descriptor_creator=std::make_unique<SkyBoxDescriptor>();
    skybox_descriptor_creator->CreateSkyBoxDescriptor(m_logical_device->get(),skybox_texture_sampler->get(),skybox_texture_image_views,skybox_descriptor_set->get());
    activeLayouts.push_back(skybox_descriptorSet_layout->get());
    //------skyBox descriptor set creating------------------------>

    //---------pipeline layout-----
    m_pipeline_layout=std::make_unique<PipelineLayout>(m_logical_device->get(),activeLayouts); //set0-->Basic_Descriptor_Set
    //--------pipleine layout-------------------
    //-------graphics pipelines-----------------------------
    cube_pipeline=std::make_unique<GraphicsPipeline>(m_logical_device->get(),m_renderPass->get(),m_pipeline_layout->get(),m_swapchain->getExtent(),"base.vert.spv","base.frag.spv",false);

    skybox_pipeline=std::make_unique<GraphicsPipeline>(m_logical_device->get(),m_renderPass->get(),m_pipeline_layout->get(),m_swapchain->getExtent(),"skybox.vert.spv","skybox.frag.spv",true);
    //-------------------------------------------------------------
    m_command_handle->allocateCommandBuffers(MAX_FRAMES_IN_FLIGHT);

}

App::~App(){
    if(m_logical_device){
        vkDeviceWaitIdle(m_logical_device->get()); //wait for other resources to finsih deallocation before deallocating the logical device
    }
    
}


void App::Run(){
    //std::cout<<"engine initiated"<<std::endl;
    float lastFrameTime=static_cast<float>(glfwGetTime());    
    while(!m_glfw_window.ShouldCloseWindow()){
        m_glfw_window.pollEvents();

        float currentFrameTime=static_cast<float>(glfwGetTime());
        float delta_Time=currentFrameTime-lastFrameTime;
        lastFrameTime=currentFrameTime;
        UpdateUniformBuffer(delta_Time);  //the unoform buffer in the gpu is now updated with the updated projection and view matric for this frame and now we need to multiply each of the model's vertices with these 
        DrawFrame();
    } 
    vkDeviceWaitIdle(m_logical_device->get());
}