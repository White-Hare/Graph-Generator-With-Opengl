#ifndef WINDOW_H
#define WINDOW_H


#include <GLFW3\glfw3.h>

void framebuffer(GLFWwindow* window, int widht, int height);
GLFWwindow* CreateWindow(GLFWwindow* window,int widht,int height);

void BirdsSee(GLFWwindow* Window, int width, int heigth, Draw object,float deltatime);
void Mouse(GLFWwindow* Window, int);
void charbuffer(GLFWwindow* Window, unsigned int codepoint);
void Keyboard(GLFWwindow* window, float deltatime);



#endif