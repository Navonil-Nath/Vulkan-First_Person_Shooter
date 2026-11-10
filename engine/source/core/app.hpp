#ifndef APP_CLASS
#define APP_CLASS
#include<iostream>
#include<stdexcept>
#include"AppTestRunner.hpp"
#include"AppUi.hpp"
#include"glfw_window.hpp"
#include<memory>
#include"instance.hpp"
#include"window_surface.hpp"
#include"AppTestRunner.hpp"
#include"glfw_window.hpp"
#include"swapchainSupport.hpp"
#include"physicalDevice.hpp"
#include"logical_device.hpp"
#include"swapchain.hpp"
#include"swapchainImageView.hpp"
#include"depth_image.hpp"
#include"renderpass.hpp"
#include"framebuffer.hpp"
#include"command.hpp"
#include"sync.hpp"
#include"vertex.hpp"
#include"shaderModule.hpp"
#include"DescriptorSetLayout.hpp"
#include"Indexbuffer.hpp"
#include"pushConstant.hpp"
#include"Stagingbuffer.hpp"
#include"UniformBuffer.hpp"
#include"Vertexbuffer.hpp"
#include"pipelineLayout.hpp"
#include"graphicsPipeline.hpp"
#include"DescriptorPool.hpp"
#include"TextureSampler.hpp"
#include"DescriptorSet.hpp"
#include"DescriptorSetLayout.hpp"
#include"cubeTextureDescriptor.hpp"
#include"GLTF_TextureDescriptor.hpp"
#include"shadowMapDescriptor.hpp"
#include"skyboxDescriptor.hpp"
#include"uniformBufferDescriptor.hpp"
#include"reflectioncubemapDescriptor.hpp"
#include"TextureImages.hpp"
#include"makeimages_and_views.hpp"
#include"imageLoader.hpp"
#include"cubeMeshData.hpp"


class AppTestRunner;

class App{
    public:
    friend class AppTestRunner;
    int WIDTH=900;
    int HEIGHT=900;
    int MAX_FRAMES_IN_FLIGHT=3;
    App();
    ~App();

    App(const App&)=delete;
    App& operator=(const App&)=delete;

    

    void Run();
    private:
        Window m_glfw_window{WIDTH,HEIGHT,"fps Window"};
        std::unique_ptr<VulkanInstance>m_vulkan_instance;
        std::unique_ptr<WindowSurface>m_window_surface;
        std::unique_ptr<PhysicalDevice>m_physical_Device;
        std::unique_ptr<LogicalDevice>m_logical_device;
        std::unique_ptr<Swapchain>m_swapchain;
        std::unique_ptr<SwapchainImageView>m_swapchainImageView;
        std::unique_ptr<DepthResource>m_depthResource;
        std::unique_ptr<RenderPass>m_renderPass;
        std::unique_ptr<FrameBuffer>m_frambuffer_handle;
        std::unique_ptr<CommandBuffer>m_command_handle;
        std::unique_ptr<SyncObjects>m_sync_objects;
        //------------------------
        //std::unique_ptr<Texture_Image>image //to be declared once evry texture image
        //------------------------
        //-----------global resources------------------------------------------------
        std::unique_ptr<PipelineLayout>m_pipeline_layout;
        std::vector<VkDescriptorSetLayout>activeLayouts; 
        PushConstantObject pushConstant;
        std::unique_ptr<DescriptorPool>m_Descriptor_Pool;
        std::unique_ptr<TextureSampler>m_texture_sampler; 
        std::unique_ptr<UniformBuffer>m_uniform_buffer;
        std::unique_ptr<CreateImage>m_image_and_view_maker;

        //-----------------------------------------------

        //-------cube ---------------------------------
        std::vector<std::unique_ptr<Texture_Image>>m_cube_textures;
        std::vector<VkImageView>m_cube_textures_imageViews;
        std::unique_ptr<DescriptorSet>cube_descriptor_set;
        const std::vector<std::string>cubeTexturesPath={
            "./Resources/cube_textures/face_one.png",
            "./Resources/cube_textures/face_two.png",
            "./Resources/cube_textures/face_three.png",
            "./Resources/cube_textures/face_four.png",
            "./Resources/cube_textures/face_five.png",
            "./Resources/cube_textures/face_six.png"

        };

        std::unique_ptr<DescriptorSetLayout>cube_texture_layout;

        std::unique_ptr<cubeTextureDescriptor>m_cube_texture_descriptor;

        std::unique_ptr<VertexBuffer>m_cube_Vertex_Buffer;
        std::unique_ptr<IndexBuffer>m_cube_Index_Buffer;

        //----------------cube-------------------------------
              
        //----------------uniformbuffer descriptor--------------
        std::unique_ptr<DescriptorSet>uniform_buffer_set;
        std::unique_ptr<DescriptorSetLayout>uniform_descriptor_set_layout;
        std::unique_ptr<UniformBufferDescriptor>uniform_descriptor_creator;

        std::vector<VkDescriptorSetLayoutBinding>uniform_buffer_bindings;
        

        //----------------uniformBuffer Descriptor----------------

        //----------------Skybox Descriptors----------------------
        const std::string skyBoxTexturePath="./Resources/skybox_cubemap/resting_place_4k.hdr";
        std::unique_ptr<TextureSampler>  skybox_texture_sampler;
        std::unique_ptr<Texture_Image> skybox_image_and_view;
        std::unique_ptr<DescriptorSetLayout>  skybox_descriptorSet_layout;
        std::unique_ptr<DescriptorSet> skybox_descriptor_set;
        std::unique_ptr<SkyBoxDescriptor> skybox_descriptor_creator;
        std::vector<VkDescriptorSetLayoutBinding> skybox_layout_bindings;


        //----------------SkyBox descriptors----------------------------------------
};

#endif

/*

now we have initilised the descriptor sets contains uniform buffer,skybox vkImage,the different textures of a cube-->at the set "baseDescriptor_Set"
and the normal map,shadow map,base/diffuse map at the set -->"materialPropDescriptor_Set"
and the reflection cubemap to hold the reflection image on the surface of a object at the set -->"reflectionCubeMap_Descriptor_Set"

*/