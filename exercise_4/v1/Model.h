#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <iterator> // for std::size()
#include <string>

#include"models/bushes.h"
#include"models/gift.h"
#include"models/sphere.h"
#include"models/suzi_flat.h"
#include"models/suzi_smooth.h"
#include"models/tree.h"

class Model
{
public:
	Model();
	Model(const char mod[]);
	void setPoint(float arr[], int size);
	void setPoint(const float arr[], int size);
	void setPoint();
	int drawModel();
	

private:
	GLuint VBO;
	GLuint VAO;
	int triangles;
};

