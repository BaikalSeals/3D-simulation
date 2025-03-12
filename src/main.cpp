#define GLM_ENABLE_EXPERIMENTAL

#include "../include/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Shader.h"
#include "../include/VAO.h"
#include "../include/VBO.h"
#include "../include/EBO.h"
#include "../include/stb/stb_image.h"
#include "../include/texture.h"
#include "../include/Camera.h"


GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

//The indices are the order for the vertices
//Since we are using triangular primitives we have 3 indices per line
// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main(int, char**){

    //First we have to initialize glfw 
    glfwInit(); 

    //Next we have to pass some information to glfw in order for it
    //to know what version of OpenGL and what function we will be working
    //with. The core profile is all the new functions, while compatibility
    //is the new plus old ones. 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    //Now we create a window object and we can set the size and name of
    //the window. 
    GLFWwindow* window = glfwCreateWindow(800, 800, "Model", NULL, NULL); 

    //Error checking to ensure the window was created
    if(window == NULL){
        std::cout << "Failed to create window" << std::endl; 
        glfwTerminate(); 
        return -1; 
    }

    //Next we have to set the context as the current window 
    glfwMakeContextCurrent(window); 

    //We use Glad to tell it to load needed configurations for OpenGL
    gladLoadGL(); 

    //Tell glad the viewport (area) of the window
    glViewport(0, 0, 800, 800); 

    Shader shaderProgram("../resources/default.vert", "../resources/default.frag"); 

    VAO VAO1; 
    VAO1.Bind(); 

    VBO VBO1(vertices, sizeof(vertices)); 
    EBO EBO1(indices, sizeof(indices)); 

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); 
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float))); 
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float))); 
    VAO1.Unbind(); 
    VBO1.Unbind(); 
    EBO1.Unbind();


    //Texture
    texture Monkey("../resources/Textures/Cringelordian.png", GL_TEXTURE_2D, GL_TEXTURE0,
                    GL_RGBA, GL_UNSIGNED_BYTE);
    Monkey.texUnit(shaderProgram, "tex0", 0); 

    glEnable(GL_DEPTH_TEST);

    Camera camera(800, 800, glm::vec3(0.0f, 0.0f, 2.0f)); 

    //Next we need a while loop to have the window keep existing for as
    //long as we want it to be displaying something
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate(); 

        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix"); 

        Monkey.Bind(); 
        VAO1.Bind(); 

        //Draw primitives, datatype of indices, index of indices
        //and start of index 
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); 
        glfwSwapBuffers(window); 

        //Now we need to tell it to process the events that we will 
        //pass to it
        glfwPollEvents(); 
    }

    VAO1.Delete(); 
    VBO1.Delete(); 
    EBO1.Delete();
    Monkey.Delete(); 
    shaderProgram.Delete();

    glfwDestroyWindow(window); 
    glfwTerminate(); 
    return 0; 

}