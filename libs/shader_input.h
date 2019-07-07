#ifndef SHADER_INPUTH
#define SHADER_INPUTH

/* packages for reading shader files */
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>   //for exit()
#include <iostream>

/* for matrices */
#include <glm/glm.hpp>

/* for shader class */
#include <glad/glad.h>

// a function that reads the shader file from disk
// use .c_str() to convert to char array: const char* shader = readShaderFile(...).c_str()
// Comment: std::string return by value!
std::string readShaderFile(const char* shaderPath);

// Shader class for 
//  - reading Vertex and Fragment shader code from file, compiling and linking to shader program
//  - setting uniforms (by variable name)
//  - activating shader
class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const;
    void setMat3(const std::string &name, const glm::mat3 &value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;

private:
    void checkCompileErrors(unsigned int shaderID, std::string type);    
};
  
#endif


