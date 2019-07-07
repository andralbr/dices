#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "./libs/shader_input.h"

#include "./libs/stb_image.h"

#include "./libs/camera.h"

#include <sstream>
#include <string>

// forward declarations and definitions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);



// settings / global constants
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// creating camera
Camera myCamera;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

// getting width and height of framebuffer
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    std::cout << "width = " << width << ", height = " << height << "\n";
    
// loading shaders from files
    Shader myShader("shader_simple.vs", "shader_simple.fs");
    Shader myLampShader("shaderLamp.vs", "shaderLamp.fs");

// definition of vertices and texture coordinates
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


// setting lamp position and color
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);


 // setting up vertex buffer and array object   
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
   
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// loading data to buffer ...
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float))); // normals
    glEnableVertexAttribArray(1);

// unbind object
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

// creating a light VAO "lightVAO"
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbind
    glBindVertexArray(0);   

// wireframe mode ? 
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

// enable depth test
    glEnable(GL_DEPTH_TEST);

        // setting projection matrix
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);

        myShader.use();
        myShader.setMat4("projection", projection);
        myShader.setVec3("lightColor", lightColor);

        myLampShader.use();
        myLampShader.setMat4("projection", projection);


/* --------------------------------------------------------------------------------
 *  RENDER LOOP ...                                                                      
 * -------------------------------------------------------------------------------- 
 */
    while (!glfwWindowShouldClose(window))
    {
   // time keeping
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

   // input 
        processInput(window);

   // clear buffers before current drawing step 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // drawing light source ...
        myLampShader.use();
        glBindVertexArray(lightVAO);
        glm::vec3 lampPosition = 1.5f * glm::vec3((float) cos(0.5 * glfwGetTime() ), 0.0f, (float) sin(0.5 * glfwGetTime()) );

        // calculating model matrix
        glm::mat4 modelLamp = glm::mat4(1.0f);
        modelLamp = glm::translate(modelLamp, lampPosition);
        //model = glm::rotate(model, 0.3f, glm::vec3(1.0f, 0.0f, 0.0f); // (float) glfwGetTime() * (float) pow(-1,i)
        modelLamp = glm::scale(modelLamp, glm::vec3(0.2f, 0.2f, 0.2f));
        
        // setting model and view matrix
        myLampShader.setMat4("model", modelLamp); 
        myLampShader.setMat4("view", myCamera.getViewMatrix() );

        glDrawArrays(GL_TRIANGLES, 0, 36);

   // drawing objects ....
        myShader.use();
        glBindVertexArray(VAO);
        myShader.setMat4("view", myCamera.getViewMatrix() );
        myShader.setVec3("lightPos", lampPosition);

    // drawing cube ....
        // model matrix
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::rotate(model, 3.14f / 4.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // (float) glfwGetTime() * (float) pow(-1,i)
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            myShader.setMat4("model", model);    

        // model matrix for normals
            glm::mat3 modelNormal = glm::transpose(glm::inverse(model));
            //glm::mat3 modelNormal = model;
            myShader.setMat3("modelNormal", modelNormal);    
          //  std::cout << glm::to_string(modelNormal) << "\n";
        

            myShader.setVec3("viewPos", myCamera.getPosition());


            glDrawArrays(GL_TRIANGLES, 0, 36);


        
        // swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}





// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W))
        myCamera.processKeyboard(MOVE_FORWARD, deltaTime);  

    if (glfwGetKey(window, GLFW_KEY_S))
        myCamera.processKeyboard(MOVE_BACKWARD, deltaTime); 

    if (glfwGetKey(window, GLFW_KEY_D))
        myCamera.processKeyboard(MOVE_RIGHT, deltaTime);  

    if (glfwGetKey(window, GLFW_KEY_A))
        myCamera.processKeyboard(MOVE_LEFT, deltaTime);  

    if (glfwGetKey(window, GLFW_KEY_UP))
        myCamera.processKeyboard(PITCH_UP, deltaTime);   

    if (glfwGetKey(window, GLFW_KEY_DOWN))
        myCamera.processKeyboard(PITCH_DOWN, deltaTime); 

    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        myCamera.processKeyboard(YAW_RIGHT, deltaTime); 

    if (glfwGetKey(window, GLFW_KEY_LEFT))
        myCamera.processKeyboard(YAW_LEFT, deltaTime); 

    if (glfwGetKey(window, GLFW_KEY_R))
        myCamera.processKeyboard(ROLL_RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_E))
        myCamera.processKeyboard(ROLL_LEFT, deltaTime);                                                          
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


