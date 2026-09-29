find_program(GLSLC glslc HINTS  "$ENV{VulkanSDK/1.4.335.0/Bin}")
#if yes then the GLSLC shall contain the VulkanSDK/1.4.335.0/Bin/glslc.exe

if(GLSLC)(
    add_custom_command(
        TARGET Kitten_Engine POST_BUILD
        COMMAND ${GLSLC} ${CMAKE_CURRENT_SOURCE_DIR}/engine/shaders/base.vert -o $<TARGET_FILE_DIR:Kitten_Engine>/base.vert.spv
        COMMAND ${GLSLC} ${CMAKE_CURRENT_SOURCE_DIR}/engine/shaders/base.frag -o $<TARGET_FILE_DIR:Kitten_Engine>/base.frag.spv
        COMMENT "compiling the shaders....."
    )
)
endif()

#lets copy the Resources folder to the folder containing thr executable
#the Resources folder contains the 3d moddels and the animated models

add_custom_command(
    TARGET Kitten_Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/engine/Resources $<TARGET_FILE_DIR:Kitten_Engine>/Resources
    COMMENT "copying the Resources folder to theexecutable directory...."
)

