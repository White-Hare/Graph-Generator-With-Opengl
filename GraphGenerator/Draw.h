#ifndef DRAW_H
#define DRAW_H

#include<iostream>
#include<GLEW\glew.h>

 class Draw {
	unsigned int VAO, VBO;
	unsigned int objectSize;
	std::string vertexStr, fragmentStr, geometryStr;
    bool Error(unsigned int shader, std::string type);
   public:
	   unsigned shaderProgram;

	   Draw(const char* vertexShader, const char* fragmentShader, const char* geometryShader=nullptr);
	   void Shader(bool geometryShader);
	   void Columns(unsigned int sizeofobject, float* object);
	   void Line(unsigned int sizeofobject, float* object);
	   void Drawer(GLenum mode, unsigned int objectsize);
};



#endif // !DRAW_H
