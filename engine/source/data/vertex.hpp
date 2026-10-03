/*
                                    Theory---
now i will create the structures which describes what each vertex is ,what attributes it contains and a function that describes how tomap the 
vertex attribute data of each vertex from this c++ struct to the vertex input attributes of the shader modules.

Then we will create a shadermodule c++ struct which first retrieves the raw spv data fromthe disk stores them in a vector and then wraps them
into VkShaderModule so that our pipeline can use the vertex and fragment shader

also i will try to gove a proper theory explanations of the vertex shader inputs like the descriptor sets and binding nos etc \
but only when we reach to that topic later , so hang on....

*/

#ifndef VERTEX_CLASS
#define VERTEX_CLASS
#include<iostream>
#include<stdexcept>
#include<vulkan/vulkan.h>
#include<glm/glm.hpp>
#include<algorithm>
#include<array>

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    float texture_index;

    static VkVertexInputBindingDescription getBindingDescription(){
        VkVertexInputBindingDescription inputBindingDescription{};
        inputBindingDescription.binding=0; //this binding position acts a s slot where all the vertices flows through
        inputBindingDescription.stride=sizeof(Vertex);
        inputBindingDescription.inputRate=VK_VERTEX_INPUT_RATE_VERTEX; //just as i told above

        return inputBindingDescription;

    }
    //now we will set the locations for each attribute n that binding position
    static std::array<VkVertexInputAttributeDescription,4> getAllAttributes(){ //one VkVertexInputAttributeDescription for each attribute
        std::array<VkVertexInputAttributeDescription,4> description;

        //location=0 description[0]-->position attribute of the vertex
        description[0].binding=0;
        description[0].location=0;
        description[0].format=VK_FORMAT_R32G32B32_SFLOAT;
        description[0].offset=offsetof(Vertex,position);

        //location=1, description[1]-->normal attribute of the Vertex struct also normal is a face value ie caculated for each face and then stored per vertex of each face
        description[1].binding=1;
        description[1].location=1;
        description[1].format=VK_FORMAT_R32G32B32_SFLOAT;
        description[1].offset=offsetof(Vertex,normal);


        //location=2
        //descripton[2]-->uv attribute of the vertex struct
        description[2].binding=2;
        description[2].location=3;
        description[2].format=VK_FORMAT_R32_SFLOAT;
        description[2].offset=offsetof(Vertex,uv); 
        //an uv of a vertex is the locationon the texture image to which that vertex must get connected to..

        //location=3
        //description[3] -->texture index of the texture form the array containing all the texture images(will be defining later)
        description[3].binding=3;
        description[3].location=3;
        description[3].format=VK_FORMAT_R32_SFLOAT;
        description[3].offset=offsetof(Vertex,texture_index);

        return description;

    }


};



#endif

