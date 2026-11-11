#include"camera.hpp"
#include<algorithm>
#include<cmath>

Camera::Camera(glm::vec3 cameraPosition):m_position(cameraPosition){};

glm::vec3 Camera::getFront(){
    glm::vec3 front{};
    front.x=std::cos(glm::radians(yaw))*std::cos(glm::radians(pitch));
    front.y=std::sin(glm::radians(pitch));
    front.z=std::sin(glm::radians(yaw))*std::cos(glm::radians(pitch));

    return glm::normalize(front);


}

glm::mat4 Camera::getViewMatrice(){
    glm::vec3 front= getFront();
    
    return glm::lookAt(m_position,m_position+front,globalUp);



}

glm::mat4 Camera::getProjectionMatrice(float aspectRatio){
    glm::mat4 proj = glm::perspective(glm::radians(fview),aspectRatio,nearPlane,farPlane);
    //now inthe vulkan coordinate system the y(+) is downwards
    //so we inverse the y coordinates
    proj[1][1]*=-1.0f;
    return proj;
    
}

void Camera::ProcessInput(GLFWwindow* window,float deltaTime){//takes the input from the user and updates the matrices accordinglly
    glm::vec3 Front_Vector=getFront();
    glm::vec3 right=glm::normalize(glm::cross(Front_Vector,globalUp)); //cross producr of the front vector and the globalUp vector
    //not that here the globalUp is the unoversal vector always pointiing to the +y axis
    float movementSpeed_mycomp=movementSpeed*deltaTime;  //this ensures that equal distance is covered in equal time in the game coordinates irrespective of the frame rates
    
    //getting the keyboard input from the user
    if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)m_position+=Front_Vector*movementSpeed_mycomp; 
    if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)m_position-=Front_Vector*movementSpeed_mycomp; 
    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)m_position+=right*movementSpeed_mycomp; 
    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)m_position-=right*movementSpeed_mycomp; 
    if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)m_position+=globalUp*movementSpeed_mycomp; 
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)m_position-=globalUp*movementSpeed_mycomp;   


    //for now i will implement a system where we click the rightMouse button to look around<will update it to seemless clickless view around later>
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS){
        //make the cursor disabled in this stare
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

        double currentMouseX=0.0f;
        double currentMouseY=0.0f;
        //get the current mouse coordinates
        glfwGetCursorPos(window,&currentMouseX,&currentMouseY);

        if(isFirstFrame){
            last_mouse_posX=currentMouseX;
            last_mouse_posY=currentMouseY;
            isFirstFrame=false;
        }

        float offsetX=static_cast<float>(currentMouseX-last_mouse_posX);
        float offsetY=static_cast<float>(currentMouseY-last_mouse_posY);

        last_mouse_posX=currentMouseX;  //for the next frame
        last_mouse_posY=currentMouseY;  // ..

        //update the camera rotation/position along the x and y axis
        //x axis
        yaw+=offsetX;
        pitch=std::clamp(pitch+offsetY,-89.0f,89.0f); //here i am clipping the maximum view in the upwards(89.0f) and the maximum downward view/rotation (-89.0f);
    

    }
    else{
        //if the right button is not clicked
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
        isFirstFrame=true; 
    }
}
