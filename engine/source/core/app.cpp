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
    //-------------basic descriptor set---------------------------------------------------------------------
    std::vector<VkDescriptorSetLayoutBinding> basic_descriptor_bindings(4);

    //binding 0 ->it shall contain descriptor pointing to the UniformBufferObject in the gpu memeory
    basic_descriptor_bindings[0].binding=0;
    basic_descriptor_bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    basic_descriptor_bindings[0].descriptorCount=1;
    basic_descriptor_bindings[0].stageFlags=VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    basic_descriptor_bindings[0].pImmutableSamplers=nullptr; //their is no sampler for the buffer data


    //binding 1 -->it shall contain the array of descriptors each containing a textures for the cube
    basic_descriptor_bindings[1].binding=1;
    basic_descriptor_bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    basic_descriptor_bindings[1].descriptorCount=6; //one descriptor holding one texture image view
    basic_descriptor_bindings[1].stageFlags= VK_SHADER_STAGE_FRAGMENT_BIT;
    basic_descriptor_bindings[1].pImmutableSamplers=nullptr;


    //binding 2 -->it shall contain the shadow depth image view
    basic_descriptor_bindings[2].binding=2;
    basic_descriptor_bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    basic_descriptor_bindings[2].descriptorCount=1;
    basic_descriptor_bindings[2].stageFlags= VK_SHADER_STAGE_FRAGMENT_BIT;
    basic_descriptor_bindings[2].pImmutableSamplers=nullptr;

    //binding 3--> it shall contain the skybox cubemap image view

    basic_descriptor_bindings[3].binding=3;
    basic_descriptor_bindings[3].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    basic_descriptor_bindings[3].descriptorCount=1;
    basic_descriptor_bindings[3].stageFlags=VK_SHADER_STAGE_FRAGMENT_BIT;
    basic_descriptor_bindings[3].pImmutableSamplers=nullptr;

    Basic_Descriptor_Set_Layout=std::make_unique<DescriptorSetLayout>(m_logical_device->get(),basic_descriptor_bindings);
    Basic_Descriptor_Set=std::make_unique<DescriptorSet>(m_logical_device->get(),Basic_Descriptor_Set_Layout->get(),m_Descriptor_Pool->get());



    //--vector containing all the layouts----------------------
    activeLayouts.push_back(Basic_Descriptor_Set_Layout->get());

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