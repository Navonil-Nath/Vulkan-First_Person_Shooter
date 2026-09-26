set(SOURCES
"./core/app.cpp"
"./Tests/AppTestRunner.cpp"
"./UI/AppUi.cpp"

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

)

target_link_libraries(${PROJECT_NAME} PRIVATE 
Vulkan::Vulkan
glfw
glm::glm

)