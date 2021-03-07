//
//  main.cpp
//  hw1.1
//
//  Created on 16/1/21.
//  Using Mac
 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#define GLEW_STATIC
 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
 
#define numVAOs 1
GLuint renderingProgram;
GLuint vao[numVAOs];
 
GLuint createShaderProgram(){
    const char *vshaderSource=
    "#version 410 \n"
    "void main(void)\n"
    "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";
    
    const char *fshaderSource=
    "#version 410 \n"
    "out vec4 color;\n"
    "void main(void) \n"
    "{color = vec4(0.0, 0.0, 1.0, 1.0);}";
    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);
    
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    
    return vfProgram;
}
 
void init(GLFWwindow* window){
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}
 
float s = 30.0f;
float inc = 0.25f;
 
void display(GLFWwindow* window, double currentTime){
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(renderingProgram);
    s += inc;
    if(s > 100.0f) inc = -0.25f;
    if(s < 30.0f) inc = 0.25f;
    glPointSize(s);
    glDrawArrays(GL_POINTS, 0, 1);
}
 
int main(void) {
    if(!glfwInit()){exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(600, 600, "Homework 1 - Question 1", NULL, NULL);
    int actualScreenWidth, actualScreenHeight;
    glfwGetFramebufferSize(window, &actualScreenWidth, &actualScreenHeight);
    
    glfwMakeContextCurrent(window);
    glViewport(0, 0, actualScreenWidth, actualScreenHeight);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){exit(EXIT_FAILURE);}
    glfwSwapInterval(1);
    
    init(window);
    
    while(!glfwWindowShouldClose(window)){
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
