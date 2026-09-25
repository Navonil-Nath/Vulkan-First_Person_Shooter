set(SOURCES
"./core/app.cpp"
"./Tests/AppTestRunner.cpp"
"./UI/AppUi.cpp"

)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    "${glfw_SOURCE_DIR}/include"
    "${glfw_SOURCE_DIR}/src"
    "./core"
    "./Tests"
    "./UI"

)

target_link_libraries(${PROJECT_NAME} PRIVATE 
glfw

)