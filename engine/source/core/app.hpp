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
#include"VertexBuffer.hpp"
#include"pipelineLayout.hpp"
#include"graphicsPipeline.hpp"
#include"DescriptorPool.hpp"
#include"TextureSampler.hpp"
#include"DescriptorSet.hpp"
#include"DescriptorSetLayout.hpp"
#include"baseDescriptor.hpp"
#include"normalDescriptor.hpp"
#include"reflectioncubemapDescriptor.hpp"



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
        std::unique_ptr<DescriptorSetLayout>descriptorSetLayout_one;
        std::unique_ptr<IndexBuffer>indexbuffer_one;
        PushConstantObject pushconstant_one;
        std::unique_ptr<StaggingBuffer>stagingbuffer_one;
        std::unique_ptr<UniformBuffer>uniformbuffer_one;
        std::unique_ptr<VertexBuffer>vertexbuffer_one;
        std::unique_ptr<PipelineLayout>pipelineLayout_one;
        std::unique_ptr<GraphicsPipeline>graphicsPipleine_one;
        std::unique_ptr<DescriptorPool>descriptor_pool;
        std::unique_ptr<TextureSampler>texture_sampler;
        std::unique_ptr<DescriptorSet>baseDescriptor_Set;
        std::unique_ptr<DescriptorSet>materialPropDescriptor_Set;
        std::unique_ptr<DescriptorSet>reflectionCubeMap_Descriptor_Set;

        std::unique_ptr<DiffuseImage> m_DiffuseImage;
        std::unique_ptr<NormalDescriptor>m_NormalDescriptor;
        std::unique_ptr<ReflectionDescriptor>m_ReflectionDescriptor;
        //now whenver we need to create a descriptor just pass in the set and other parametes to the respective functions of these three above objects
        
};

#endif

/*

now we have initilised the descriptor sets contains uniform buffer,skybox vkImage,the different textures of a cube-->at the set "baseDescriptor_Set"
and the normal map,shadow map,base/diffuse map at the set -->"materialPropDescriptor_Set"
and the reflection cubemap to hold the reflection image on the surface of a object at the set -->"reflectionCubeMap_Descriptor_Set"
*/