set(SOURCES
"./core/app.cpp"
"./Tests/AppTestRunner.cpp"
"./UI/AppUi.cpp"
"./surface/window_surface.cpp"
"./Tests/AppTestRunner.cpp"
"./UI/AppUi.cpp"
"./vendor/stb_image.cpp"
"./vulkan_instance/instance.cpp"
"./Window/glfw_window.cpp"
"main.cpp"
"./device/swapchainSupport.cpp"
"./device/physicalDevice.cpp"
"./device/logical_device.cpp"
"./device/swapchain.cpp"
"./device/swapchainImageView.cpp"
"./DepthResource/depth_image.cpp"
"./pipeline/renderpass.cpp"
"./pipeline/framebuffer.cpp"
"./command/command.cpp"
"./sync/sync.cpp"
"./data/shaderModule.cpp"
"./Buffers/Stagingbuffer.cpp"
"./Buffers/Indexbuffer.cpp"
"./Buffers/Vertexbuffer.cpp"
"./Buffers/UniformBuffer.cpp"
#"./Buffers/pushConstant.cpp"
"./Buffers/DescriptorSetLayout.cpp"
"./pipeline/pipeLineLayout.cpp"
"./pipeline/graphicsPipeline.cpp"
"./texture/DescriptorPool.cpp"
"./texture/TextureSampler.cpp"
"./DescriptorSet/DescriptorSet.cpp"
"./DescriptorSet/Descriptor/cubeTextureDescriptor.cpp"
"./DescriptorSet/Descriptor/GLTF_TextureDescriptor.cpp"
"./DescriptorSet/Descriptor/shadowMapDescriptor.cpp"
"./DescriptorSet/Descriptor/skyboxDescriptor.cpp"
"./DescriptorSet/Descriptor/reflectioncubemapDescriptor.cpp"
"./DescriptorSet/Descriptor/uniformBufferDescriptor.cpp"
"./texture/imageLoader.cpp"
"./texture/TextureImages.cpp"
"./texture/makeimages_and_views.cpp"
"./Camera/camera.cpp"


)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    "${glfw_SOURCE_DIR}/include"
    "${glfw_SOURCE_DIR}/src"
    "${Vulkan_SOURCE_DIR}/include"
    "${glm_SOURCE_DIR}/glm"
    "${glm_SOURCE_DIR}/ext"
    "${glm_SOURCE_DIR}/gtc"
    "./core"
    "./Tests"
    "./UI"
    "./surface"
    "./vendor"
    "./vulkan_instance"
    "./Window"
    "./device"
    "./DepthResource"
    "./pipeline"
    "./command"
    "./sync"
    "./data"
    "./Buffers"
    "./texture"
    "./DescriptorSet"
    "./DescriptorSet/Descriptor"
    "./Camera"
    
    
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
Vulkan::Vulkan
glfw
glm::glm

)

find_program(GLSLC glslc HINTS  "$ENV{VULKAN_SDK}/Bin")
#if yes then the GLSLC shall contain the VulkanSDK/1.4.335.0/Bin/glslc.exe

if(GLSLC)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${GLSLC} ${CMAKE_SOURCE_DIR}/engine/shaders/base.vert -o $<TARGET_FILE_DIR:${PROJECT_NAME}>/base.vert.spv
        COMMAND ${GLSLC} ${CMAKE_SOURCE_DIR}/engine/shaders/base.frag -o $<TARGET_FILE_DIR:${PROJECT_NAME}>/base.frag.spv
        COMMENT "compiling the shaders....."
    )

endif()

#lets copy the Resources folder to the folder containing thr executable
#the Resources folder contains the 3d moddels and the animated models

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/engine/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
    COMMENT "copying the Resources folder to the executable directory...."
)

