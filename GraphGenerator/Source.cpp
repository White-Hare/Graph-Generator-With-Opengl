#include<iostream>
#include<vector>
#include"Objects.h"
#include"Window.h"
#include<GLM\gtc\matrix_transform.hpp>
#include<GLM\glm.hpp>
#include<GLM\gtc\type_ptr.hpp>
#include"MTReader.h"

GLFWwindow* Window;


void MainLoop();

std::vector <float> columnlines;
std::vector <float> linesofgraph;

int main() {

	glfwInit();

	Window = CreateWindow(Window, 600, 600);

	GLenum glewenum=glewInit();

	if (glewenum != GLEW_OK) {
		std::cout << "ERROR:GLEW hasn't started successfully" << std::endl;
		system("pause");
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_POINT_SIZE);//learn it
	glfwSwapInterval(0);

	int index = 0;
	float shrinksize=0.05;
	for (int i = -500; i <= 500; i+=1) {
		columnlines.push_back((float)i*shrinksize);
		//std::cout << index << '-' << columnlines[index++] << std::endl;
		columnlines.push_back(0.0f);
		//std::cout << index << '-' << columnlines[index++] << std::endl;
	}

	for (int i = -500; i <= 500; i+=1) {
		columnlines.push_back(0.0f);
		//std::cout << index << '-' << columnlines[index++] << std::endl;
		columnlines.push_back((float)i*shrinksize);
		//std::cout << index<<'-'<<columnlines[index++] << std::endl;
		
	}
	/*
	index = 0;
	
	for (int x = -500; x <= 500; x++) {

		linesofgraph[index++] = (float)x*shrinksize;
		//std::cout << index << std::endl;
		//if (x > 3) {
			linesofgraph[index++] = pow((float)x,2) * shrinksize;
			//std::cout << index << std::endl;
		}
		else {
			linesofgraph[index++] =  (x+4) * shrinksize;
			std::cout << index << std::endl;
		}
		}*/


	//MTR
	MTR March("Log.txt");
	std::vector <std::string>  logf = March.datavec();
	size_t filesize = logf.size();
	
	std::string::size_type sz;

	unsigned int vecsize= logf.size();

	std::cout << vecsize << std::endl;
	for (int i = 0;i<vecsize;i++) {

	    
		linesofgraph.push_back(stof(logf[i++], &sz)*1*shrinksize);
		linesofgraph.push_back(stof(logf[i], &sz)*1*shrinksize);

	}


	//~MTR


	column.Shader(true);
	column.Columns(columnlines.size()*sizeof(float), &columnlines[0]);

	grid.Shader(true);
	grid.Columns(columnlines.size() * sizeof(float),&columnlines[0]);

	line.Shader(false);
	line.Columns(linesofgraph.size()*sizeof(float) ,&linesofgraph[0]);

	point.Shader(true);
	point.Columns(linesofgraph.size()*sizeof(float), &linesofgraph[0]);

	glUseProgram(line.shaderProgram);
	glUniform3fv(glGetUniformLocation(line.shaderProgram, "Color"), 1, &glm::vec3(1.0,0.0,0.0)[0]);
	//glUniform1f(glGetUniformLocation(line.shaderProgram, "screenRatio"),  600/600);

	glUseProgram(point.shaderProgram);
	glUniform3fv(glGetUniformLocation(point.shaderProgram, "Color"), 1, &glm::vec3(1.0, 0.0, 0.0)[0]);
	//glUniform1f(glGetUniformLocation(point.shaderProgram, "screenRatio"), 600 / 600);

	glUseProgram(column.shaderProgram);
	//glUniform1f(glGetUniformLocation(column.shaderProgram, "screenRatio"),600/600);
	glUniform1f(glGetUniformLocation(column.shaderProgram, "size"), 0.025);

	glUseProgram(grid.shaderProgram);
	glUniform3fv(glGetUniformLocation(grid.shaderProgram, "Color"), 1, &glm::vec3(0.2, 0.2, 0.2)[0]);
	//glUniform1f(glGetUniformLocation(grid.shaderProgram, "screenRatio"), 600 / 600);
	glUniform1f(glGetUniformLocation(grid.shaderProgram, "size"), 40);

	MainLoop();

	return 0;
}

void MainLoop() {

	int width = 600,height=600;
	int lastwidth = width, lastheigth = height;
	float current, last = 0, delta;
	glm::mat4 projection = glm::perspective(glm::radians(0.0f), (float)width / (float)height, -0.1f, 0.1f);


	while (!glfwWindowShouldClose(Window))
	{
		current = (float)glfwGetTime();
		delta = current - last;
		last = current;


		glClearColor(0.15, 0.15, 0.15, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		Keyboard(Window,delta);


		//glfwSetCharCallback(Window, charbuffer);
		glfwSetCursorEnterCallback(Window,Mouse);

		glUseProgram(grid.shaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(grid.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		BirdsSee(Window, width, height, grid,delta);
		grid.Drawer(GL_POINTS,columnlines.size() / 2);

		glUseProgram(column.shaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(column.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		BirdsSee(Window, width, height, column, delta);
		column.Drawer(GL_POINTS, columnlines.size() / 2);

		glUseProgram(line.shaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(line.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		BirdsSee(Window, width, height, line, delta);
		line.Drawer(GL_LINE_STRIP, linesofgraph.size()/2);

		glUseProgram(point.shaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(point.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		BirdsSee(Window, width, height, point, delta);
		point.Drawer(GL_POINTS, linesofgraph.size()/2);


		glfwGetWindowSize(Window, &width, &height);

		if (width != lastwidth || height != lastheigth) {
			std::cout << "width:" << width << "\theight:" << height << std::endl;
			glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
			
			lastwidth = width;
			lastheigth = height;
		}

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}



}