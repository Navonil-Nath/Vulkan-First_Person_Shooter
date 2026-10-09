/*
the unoform buffers will hold these datas:main camera view,projection matrices,point light view and projection matirces,light direction(for directional lights),light color,
view and projection matrices for the reflection cubemaps,array of bones for the skeletal animations
and the push constants will contain data like the model matrix and metallica dn roughness values of solid surfaces and animation flags
*/
#ifndef UNIFORM_BUFFER_CLASS
#define UNIFORM_BUFFER_CLASS
#include<glm/glm.hpp>
#include<cstdint>
#include<stdexcept>
#include<vulkan/vulkan.hpp>


struct UniformBufferObject{
    static constexpr uint32_t MaxDynamicReflectors=4; //no more than 4 reflecting objects in the scence
    static constexpr uint32_t ref_dir=6;
    static constexpr uint32_t max_ref_surfaces=MaxDynamicReflectors*ref_dir;
    static constexpr uint32_t totalBines=130;

    //for the main camera
    glm::mat4 view{1.0f};
    glm::mat4 projection{1.0f};
    glm::mat4 MainCameraSpace=projection*view;
    

    //for the pointlight --we will set the position and direction of the point light later
    glm::mat4 pointlightView{1.0f};
    glm::mat4 pointlightProj{1.0f};
    glm::mat4 pointLightSpace=pointlightProj*pointlightView;
    
    //for the directional light

    glm::vec4 dirlightDirection{0.5f,-1.0f,0.5f,0.0f};
    glm::vec3 dirlightColor{1.0f,1.0f,1.0f};
    glm::mat4 dirLightView{1.0f};
    glm::mat4 dirLightProj{1.0f};
    glm::mat4 dirLightSpace=dirLightProj*dirLightView;

    //for the reflective surface setting up camera positions and matrices
    //for each reflective object their would be 6 directions for the camera to take input wrt to its position
    //so the total mo of directions it will be looking at is 'max_ref_surfaces'
    glm::mat4 refl_cubeMapViews[max_ref_surfaces];
    glm::mat4 refl_cubeMapProjection[max_ref_surfaces];
    glm::mat4 refl_cubemapSpace[max_ref_surfaces];


    //for the skybox cubemap
    //this is optional beacuse in case the skybox requires a different rendering than the normal reflective surfaces
    glm::mat4 refl_skyboxView[max_ref_surfaces];
    glm::mat4 refl_skyboxProj[max_ref_surfaces];
    glm::mat4 refl_skyboxSpace[max_ref_surfaces];


    //for rigging animations
    glm::mat4 bones[200];



};

class UniformBuffer{
    public:
        UniformBuffer(VkDevice device,VkPhysicalDevice physicalDevice);
        ~UniformBuffer();

        UniformBuffer(const UniformBuffer&)=delete;
        UniformBuffer& operator=(const UniformBuffer&)=delete;

        void Upload(UniformBufferObject& object);
        uint32_t findMemory(uint32_t typeFilter,VkMemoryPropertyFlags flags);

        VkBuffer get(){return m_buffer;}
        VkDeviceMemory getMemory(){return m_memory;}

    private:
        void CreateBuffer();
        VkDevice m_device{VK_NULL_HANDLE};
        VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
        VkDeviceMemory m_memory{VK_NULL_HANDLE};
        VkBuffer m_buffer;
        VkDeviceSize m_size{0};

};
#endif