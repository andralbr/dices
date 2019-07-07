
#include "shader_input.h"

/* reading shader from file */
std::string readShaderFile(const char* shaderPath)
{
    // strings to store code
    std::string shaderCode;

    // stream variable to open and hold file
    std::ifstream shaderFile;

    // exception setup
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(shaderPath);

        // read to 'string stream' 
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        // convert to string, c-style 
        return shaderStream.str();
      
        //const char* cShaderCode = shaderCode.c_str();
        //std::cout << cShaderCode;
        //return cShaderCode;
    }
    catch(std::ifstream::failure exc)
    {
        std::cerr << "Unable to read shader file\n";
        exit(1);
    }
}




/* a shader class for
 *  - reading shader source files
 *  - linking and creating shader program
 *  - activating shader program
 *  - setting uniforms
 */

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{

    /* loading shader code */
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // exception setup
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        // read to 'string stream' 
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        // convert to string, c-style 
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure exc)
    {
        std::cerr << "Unable to read shader file\n";
        exit(1);
    }

    // converting to C-style strings
    const char* vcharCode = vertexCode.c_str();
    const char* fcharCode = fragmentCode.c_str();

    /*  setting up vertex and fragment shader */
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vcharCode, NULL);
    glShaderSource(fragmentShader, 1, &fcharCode, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // check if compilation worked
    checkCompileErrors(vertexShader, "VERTEX");
    checkCompileErrors(fragmentShader, "FRAGMENT");

    /*  creating shader program */
    ID = glCreateProgram();
        
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // check for linking errors
    checkCompileErrors(ID, "PROGRAM");

    // cleaning things up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}

/* Shader: activating Shader */
void Shader::use()
{
    glUseProgram(ID);
}

/* Shader: setting uniforms */
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
} 

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
} 

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &value) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}


void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);

}


/* helper function to check for errors at compile and linking stage */
void Shader::checkCompileErrors(unsigned int shaderID, std::string type)
{
    int success;
    char infoLog[512];

    if (type == "VERTEX" || type == "FRAGMENT")
    {
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else if (type == "PROGRAM")
    {
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success) 
        {
            glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

}


