#ifndef CUBE_MESH_DATA_CLASS
#define CUBE_MESH_DATA_CLASS

#include<vulkan/vulkan.h>
#include<stdexcept>
#include<vector>
#include"vertex.hpp"

class CubeMeshData{
    public:
        static std::vector<Vertex> getCubeVertices(){
            return {
                
                {{-0.5f,-0.5f,0.5f},{0.0f,0.0f,1.0f},{0.0f,1.0f},0.0f}, //vertex 0
                {{0.5f,-0.5f,0.5f},{0.0f,0.0f,1.0f},{1.0f,1.0f},0.0f}, //vertex 1
                {{0.5f,0.5f,0.5f},{0.0f,0.0f,1.0f},{1.0f,0.0f},0.0f},//vertex 2
                {{-0.5f,0.5f,0.5f},{0.0f,0.0f,1.0f},{0.0f,0.0f},0.0f}, //vertex 3


                {{0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},{0.0f,1.0f},1.0f}, //vertex 4
                {{-0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},{1.0f,1.0f},1.0f}, //vertex 5
                {{-0.5f,0.5f,-0.5f},{0.0f,0.0f,-1.0f},{1.0f,0.0f},1.0f}, //vertex 6
                {{0.5f,0.5f,-0.5f},{0.0f,0.0f,-1.0f},{0.0f,0.0f},1.0f}, //vertex 7


                {{-0.5f,-0.5f,-0.5f},{-1.0f,0.0f,0.0f},{0.0f,1.0f},2.0f}, //vertex 8
                {{-0.5f,-0.5f,0.5f},{-1.0f,0.0f,0.0f},{1.0f,1.0f},2.0f}, //vertex 9
                {{-0.5f,0.5f,0.5f},{-1.0f,0.0f,0.0f},{1.0f,0.0f},2.0f}, //vertex 10
                {{-0.5f,0.5f,-0.5f},{-1.0f,0.0f,0.0f},{0.0f,0.0f},2.0f}, //vertex 11

                {{0.5f,-0.5f,0.5f},{1.0f,0.0f,0.0f},{0.0f,1.0f},3.0f}, //vertex 12
                {{0.5f,-0.5f,-0.5f},{1.0f,0.0f,0.0f},{1.0f,1.0f},3.0f}, //vertex 13
                {{0.5f,0.5f,-0.5f},{1.0f,0.0f,0.0f},{1.0f,0.0f},3.0f}, //vertex 14
                {{0.5f,0.5f,0.5f},{1.0f,0.0f,0.0f},{0.0f,0.0f},3.0f}, //vertex 15

                {{-0.5f,0.5f,0.5f},{0.0f,1.0f,0.0f},{0.0f,1.0f},4.0f}, //vertex 16
                {{0.5f,0.5f,0.5f},{0.0f,1.0f,0.0f},{1.0f,1.0f},4.0f}, //vertex 17
                {{0.5f,0.5f,-0.5f},{0.0f,1.0f,0.0f},{1.0f,0.0f},4.0f}, //vertex 18
                {{-0.5f,0.5f,-0.5f},{0.0f,1.0f,0.0f},{0.0f,0.0f},4.0f}, //vertex 19

                {{-0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},{0.0f,1.0f},5.0f}, //vertex 20
                {{0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},{1.0f,1.0f},5.0f}, //vertex 21
                {{0.5f,-0.5f,0.5f},{0.0f,-1.0f,0.0f},{1.0f,0.0f},5.0f}, //vertex 22
                {{-0.5f,-0.5f,0.5f},{0.0f,-1.0f,0.0f},{0.0f,0.0f},5.0f} //vertex 23

            };


        }

        //now the ordering of the indices inside the index buffer matters beacuse this is where 
        //the anti clockwise and clock wise noumbering has to be done ,as the gpu only renderes those primitives with the
        //anti clockwise noumbering as in front of it
        
        static std::vector<uint32_t>getIndices(){
            return {

                0,1,2, 2,3,0, //front face<anti clockwise>
                4,5,6, 6,7,4, //back face<anti clcokwise>
                8,9,10, 10,11,8, //left face<anti clcokwise>
                12,13,14, 14,15,12, //right face<anti clockwise>
                16,17,18, 18,19,16, //Top face anti clockwise'
                20,21,22, 22,23,20 //Bitt0m face anti clockwise

                
            };
        }


};
#endif

/*
                    Theory
The normal is always projected from the center of the model to its surface(face) perpendicularlly
the model is made using the standard cordinate systeam with 0,0,0 as the center of the model
later when the model is to be loaded into the scene it will be decided where in the 3d space its origin shall lie
and will be updated in its model matrix accordinglly

the vertex follows the order -->{{position},{normal},{u,v},texture_index}



*/