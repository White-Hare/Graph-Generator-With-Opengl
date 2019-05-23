#include"Objects.h"
#include"Window.h"
#include<GLM\gtc\type_ptr.hpp>
#include<iostream>
#include<fstream>

void framebuffer(GLFWwindow* window, int widht, int height) { glViewport(0, 0, widht, height); }

GLFWwindow* CreateWindow(GLFWwindow* window, int widht, int height) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(widht, height, "Graphic", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer);

	if (window == NULL) {
		std::cerr << "window hasn't been created" << std::endl;
	}

	glfwMakeContextCurrent(window);

	return window;
}

void Keyboard(GLFWwindow* window, float delta) {

	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);

	}


}

bool mouse_in_screen = 0;

void Mouse(GLFWwindow* window,int is_entered) {
		mouse_in_screen = is_entered;
}

float x = 0, y = 0;

void BirdsSee(GLFWwindow* Window,int width,int heigth,Draw object,float delta) {
	
	if (mouse_in_screen == 1) {
		double xpos = width, ypos = heigth;


		glfwGetCursorPos(Window, &xpos, &ypos);

		//std::cout << delta <<std::endl;

		if (ypos > heigth - 50 && y < 20) {
			y += 1 * delta;
		}
		if (ypos < 50 && y>-20) {
			y -= 1 * delta;
		}
		if (xpos > width - 50 && x > -20) {
			x -= 1 * delta;
		}
		if (xpos < 50 && x < 20) {
			x += 1 * delta;
		}
		//std::cout << "x-" << xpos << "\ty-" << ypos << std::endl;
		glUniform2fv(glGetUniformLocation(object.shaderProgram, "move"), 1, glm::value_ptr(glm::vec2(x, y)));
	}
}

void charbuffer(GLFWwindow* Window, unsigned int codepoint) {
	std::ofstream file("Log.txt",std::ios::app);
	file << (char)codepoint ;
	file.close();

}