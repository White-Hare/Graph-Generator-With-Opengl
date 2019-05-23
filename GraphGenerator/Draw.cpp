#include"Draw.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include<GLM\glm.hpp>
#include<GLM\gtc\type_ptr.hpp>



Draw ::Draw(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {


	std::ifstream vertexFile(vertexPath), fragmentFile(fragmentPath),geometryFile;

	// ensure ifstream objects can throw exceptions:
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	if (geometryPath != nullptr) {
		geometryFile.open(geometryPath);
		geometryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	}

	try {
		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();
		

		vertexStr = vertexStream.str();
		fragmentStr = fragmentStream.str();

		if (geometryPath != nullptr) {
		
			std::stringstream geometryStream;

			geometryStream << geometryFile.rdbuf();
			geometryFile.close();

			geometryStr = geometryStream.str();
		}

		//std::cout << vertexStr << std::endl << fragmentStr << std::endl << geometryStr << std::endl;
	}
	catch (std::ifstream::failure e) {
		std::cerr << "File Not Succesfully Read" << std::endl;
		system("pause");
	}


}

void Draw ::Shader(bool geometryShader){

	unsigned int vertexShader, fragmentShader;
	const char* vertexData = vertexStr.c_str(), *fragmentData = fragmentStr.c_str();


	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexData, NULL);
	glCompileShader(vertexShader);
	Error(vertexShader, "VERTEX");

	glShaderSource(fragmentShader, 1, &fragmentData, NULL);
	glCompileShader(fragmentShader);
	Error(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	if (geometryShader) {
		unsigned int geometryShader;
		const char* geometryData=geometryStr.c_str();
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

		glShaderSource(geometryShader, 1, &geometryData, NULL);
		glCompileShader(geometryShader);
		Error(geometryShader,"GEOMETRY");

		glAttachShader(shaderProgram, geometryShader);
		glDeleteShader(geometryShader);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(shaderProgram);
	Error(shaderProgram, "PROGRAM");
}

bool Draw ::Error(unsigned int shader, std::string type) {
	GLint success;
	GLchar infolog[512];

	if (type == "PROGRAM") {
		glGetShaderiv(shader, GL_LINK_STATUS, &success);

		if (!success) {
			std::cerr << "Program linking -ERROR-: " << infolog << std::endl;
			system("pause");
		}

	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			std::cerr << "An -ERROR- occured in " << type << " shader:" << infolog << std::endl;
			system("pause");
		}

	}
	return success;
}

	void Draw ::Columns(unsigned int sizeofobject, float* object) {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeofobject, object, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Draw ::Line(unsigned int sizeofobject, float* object) {



	}

	void Draw ::Drawer(GLenum mode,unsigned int objectsize) {
		glBindVertexArray(VAO);
		glDrawArrays(mode, 0, objectsize);
	}

