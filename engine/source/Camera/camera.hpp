/*
you will find all the code used in this file on the url:"https://docs.vulkan.org/tutorial/latest/Building_a_Simple_Engine/Camera_Transformations/04_camera_implementation.html"
here the main purpose of the Camera object is to update the Projection and the view matrix of the uniform buffer object every frame


*/
#ifndef VULKAN_CAMERA_CLASS
#define VULKAN_CAMERA_CLASS

#include<stdexcept>
#include<GLFW/glfw3.h>
#include<vulkan/vulkan.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class Camera{

    public:
        Camera(glm::vec3 cameraPosition); //we now have to spawn our model<first person> st some place other than the 0,0,0

        ~Camera()=default;

        void ProcessInput(GLFWwindow* window,float deltaTime); //delta time is used to sync the movement of the model and camera across all the device regardless of the frame rate
        //this ProcessInput takes in the user's keyboard input and updates the projection and view matrice

        glm::mat4 getViewMatrice();
        glm::mat4 getProjectionMatrice(float aspectRatio); //aspect ration is the window width/window height is used to calcuate the 'filed of view' along the horizontal range by the gpu
        glm::vec3 getPosition(){return m_position;}
        glm::vec3 getFront(); //it returns a vector which is caluated using the global up vector and the yaw and pitch at that frame of the camera.it is used to calculate the right and up vector of the camera ar a particular frame,it is also the vector which points to where the camera is looking to at that moment
        glm::vec3 globalUp{0.0f,1.0f,0.0f};


    private:
        glm::vec3 m_position{0.0f,0.0f,0.0f}; //it is the current position of the camera in a particular frame at the start of the aplication it is at 0
        float yaw{-90.0f}; //in the standard coordinate systeam the yaw represents the horizontal movement and the pitch represents the vertical upand down movement along a fixed origin
        //the yaw value of -90.f ensures that the camera faces straight to the -z axis which is +z axis accrd to the vulkan coordinate systeam
        float pitch{0.0f};
        //a pitch value of 0.0f ensures that the camera sits right at the origin when the frame starts
        float movementSpeed{3.5f}; //the pace at which the camera covers distance upon each leap
        float mouseSensitivity{0.1f}; //this is a value which determines how quick we can rotate the camera
        float fview{60.0f}; //or 60 degrees this determines the angle of the frustum through the camera and hence the field of view

        bool isFirstFrame=true; //this is ext imp to avoid dangling camera this tells the gpu that theis is the first frame and hence the current position of the camera is 0 no matter
        //where the cursor is on the screen when the application/engine boots
        double last_mouse_posX{0.0}; //when the mouse is moved to a different pos on the screen these two values holds its last x,y values nesessary to update the view and projection matrice for the new frame
        double last_mouse_posY{0.0};
        float nearPlane=0.1f; //the distance in the coordinate space that which if crossed towards the camera(its projection)the gpu won't render it to prevent the camera model clamping
        float farPlane=100.f; //the distance in the coordinate space that which if crossed away from the (its projection)the gpu won't render it

};      
#endif
