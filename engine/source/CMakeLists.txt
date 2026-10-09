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
"./Buffers/pushConstant.cpp"
"./Buffers/DescriptorSetLayout.cpp"
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
    "./Tests"
    "./UI"
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
    
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
Vulkan::Vulkan
glfw
glm::glm

)