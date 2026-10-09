/*

the push constant is used for the storing data that is passed to the shader without the 
buffers 
*/

#ifndef PUSH_CONSTANT_CLASS
#define PUSH_CONSTANT_CLASS
#include<glm/glm.hpp>
#include<iostream>
#include<stdexcept>
#include<vulkan/vulkan.hpp>

struct PushConstantObject{
    glm::mat4 model{1.0f};
    int isReflective{0};
    int cubeMapIndex{-1}; //here -1 beacuse otherwise it will always default to the texture at index 0 which is a valid slot
    float metallicFactor{1.0f};
    float roughnessFactor{1.0f};
    glm::vec4 baseColorFactor{1.0f};
    int isSkinned{0};
    int boneOffset{0};
    int isEmissive{0};
    int isViewModel{0};    

};

/*
    here the cubemapindex refes that to which side the cameraa should view now ir +x,-x,+y,-y or +z,-z
    the metallic factor and roughness and basecolor used to determine the properties object being rendered 
    isSkinned is used to determine whether the objects mesh being rendere should contain bones or not
    if value ==1 then the vertex shader will render the mesh with bones according to the bones id and vertex weight
    boneOffset is used to determine the position of the bones matrice on the uniform buffer on the gpu memeory
    isEmissive is used to determine whether the object being rendered is a glowing object or not
    isViewModel is used to determine whether the model is being viewed from the main camraa or the object own view model
*/


#endif