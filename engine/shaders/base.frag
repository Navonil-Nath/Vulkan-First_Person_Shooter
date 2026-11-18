#version 450

layout(location=0)in vec3 fragNormal;
layout(location=1)in vec2 fragUV;
layout(location=2)flat in int texIndex;

layout(location=0)out vec4 frag_Color;

layout(set=0,binding=0) uniform sampler2D cubeTextures[6];

void main(){
    frag_Color=vec4(texture(cubeTextures[texIndex],fragUV));
}


