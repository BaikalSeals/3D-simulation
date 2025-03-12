#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera{
    public:
        //Position of the camera, direction of the camera and the up direction
        //of the camera
        glm::vec3 position; 
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
        
        //Two variables to store width and height 
        int width; 
        int height; 

        //Speed of the camera as well as the sensitivity when looking around
        float speed = 0.1f;
        float sensitivity = 100.0f;

        //constructor
        Camera(int width, int height, glm::vec3 position); 

        //Function to create and send the view and projection matrix to the shader
        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform); 

        //Function to handle the inputs
        void Inputs(GLFWwindow* window); 
};

#endif