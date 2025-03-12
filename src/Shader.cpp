#include "../include/Shader.h"

//Reads the file contents
std::string get_file_contents(const char* filename){
    //Opens the file in binary form
    std::ifstream in(filename, std::ios::binary); 
    //If the file is open then continue, else throw an error
    if (in){
        //Create contents string
        std::string contents; 
        //Go to end of the line 
        in.seekg(0, std::ios::end); 
        //Resize the string to fit the file size that we
        //now know of since we went to the end of the line
        contents.resize(in.tellg()); 
        //Move back to beginning of the line
        in.seekg(0, std::ios::beg); 
        //Read contents into string and return contents
        in.read(&contents[0], contents.size()); 
        in.close(); 
        return(contents); 
    }
    throw(errno); 
};

Shader::Shader(const char* vertexFile, const char* fragmentFile){
    std::string vertexCode = get_file_contents(vertexFile); 
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str(); 
    const char* fragmentSource = fragmentCode.c_str(); 

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    //Now we need to pass the source code to it from the const *char 
    //vertexShaderSource. We give it the reference value, then specify
    //that we are only using one screen, and then passing it the source
    //code. 
    glShaderSource(vertexShader, 1, &vertexSource, NULL); 
    //In order for it to actually be able to use the source code we have
    //to compile it first which can be done with the function below:
    glCompileShader(vertexShader); 
    //We now do the same thing with the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL); 
    glCompileShader(fragmentShader); 

    //In order to use the shader we have to wrap them up in a shader
    //program and attach a shader to the shader program. 
    ID = glCreateProgram(); 
    glAttachShader(ID, vertexShader); 
    glAttachShader(ID, fragmentShader); 
    glLinkProgram(ID); 

    //We can now delete the shaders we created since they are now in the
    //program itself
    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);
};

void Shader::Activate(){

    glUseProgram(ID); 

};

void Shader::Delete(){

    glDeleteProgram(ID); 

};