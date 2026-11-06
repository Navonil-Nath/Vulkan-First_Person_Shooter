#include"app.hpp"
#include<iostream>
#include<memory>
#include<GLFW/glfw3.h>
#include<string>

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

    //--------------cube-------------------------------
   

    //forming the imageviews and putting data in memeory
    for(const std::string& path: cubeTexturesPath){
        LoadedImage rawImage=ImageLoader::loadTexture(path);
        VkDeviceSize imageSize=static_cast<VkDeviceSize>(rawImage.width,rawImage.height*4);

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

    //----------------------cube---------------------------



    //---------pipeline layout-----
    m_pipeline_layout=std::make_unique<PipelineLayout>(m_logical_device->get(),activeLayouts); //set0-->Basic_Descriptor_Set

   

}

App::~App(){
    if(m_logical_device){
        vkDeviceWaitIdle(m_logical_device->get()); //wait for other resources to finsih deallocation before deallocating the logical device
    }
    
}


void App::Run(){
    //std::cout<<"engine initiated"<<std::endl;
    while(!m_glfw_window.ShouldCloseWindow()){
        m_glfw_window.pollEvents();
    }
}