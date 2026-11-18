#version 450

layout(location=0)in vec3 fragNormal;
layout(location=1)in vec2 fragUV;
layout(location=2)flat in int texIndex;

layout(location=0)out vec4 outColor;

layout(set=2,binding=0) uniform sampler2D skyboxTextures[6];
void main(){
    outColor=vec4(texture(skyboxTextures[texIndex],fragUV));
}