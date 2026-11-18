#version 450

layout(location=0)in vec3 inPosition;
layout(location=1)in vec3 inNormal;
layout(location=2)in vec2 inUV;
layout(location=3)in float inTexIndex;

layout(location=0)out vec3 fragNormal;
layout(location=1)out vec2 fragUV;
layout(location=2)out int texIndex;


layout(set=1,binding=0)uniform UniformBufferObject{
    mat4 view;
    mat4 projection;
    mat4 MainCameraSpace; 
    mat4 pointlightView;
    mat4 pointlightProj;
    mat4 pointLightSpace;
    vec4 dirlightDirection;
    vec3 dirlightColor;
    mat4 dirLightView;
    mat4 dirLightProj;
    mat4 dirLightSpace;
    mat4 refl_cubeMapViews[24];
    mat4 refl_cubeMapProjection[24];
    mat4 refl_cubemapSpace[24]; 
    mat4 refl_skyboxView[24];
    mat4 refl_skyboxProj[24];
    mat4 refl_skyboxSpace[24];
    mat4 bones[200];
}ubo;

layout(push_constant) uniform PushConstantObject{
    mat4 model;
    int isReflective;
    int cubeMapIndex;
    float metallicFactor;
    float roughnessFactor;
    vec4 baseColorFactor;
    int isSkinned;
    int boneOffset;
    int isEmissive;
    int isViewModel; 
}pc;

void main(){
    gl_Position=ubo.MainCameraSpace*pc.model*vec4(inPosition,1.0);
    //fragNormal=mat3(inNormal);
    //fragNormal=mat3(pc.model)*inNormal; //this places the normal in th worldspace free from the translation part(position) so now the normal direction is universal

    //fragNormal=mat3(inverse(pc.model))*inNormal;//this helsp to maintain the normal propertions to the same allowing for uniform scalling along any axis but when themodel is rotated the normals are rotated in the opposite direction resulting in the normals still in the same position
    fragNormal=mat3(transpose(inverse(pc.model)))*inNormal; //this fixes the rotation problem ,so now the normals rotate along with the face
    fragUV=inUV;
    texIndex=int(round(inTexIndex));


}



