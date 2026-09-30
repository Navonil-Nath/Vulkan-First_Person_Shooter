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
    

)

target_link_libraries(${PROJECT_NAME} PRIVATE 
Vulkan::Vulkan
glfw
glm::glm

)