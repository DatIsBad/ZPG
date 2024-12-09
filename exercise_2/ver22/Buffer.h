#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include "Object.h"

class Buffer
{
public:
	Buffer();
	void addPoint(float arr[], int size);
	void addPoint(Object obj);
	void addPoint();
	void bindVAO();

private:
	GLuint VBO;
	GLuint VAO;
};

