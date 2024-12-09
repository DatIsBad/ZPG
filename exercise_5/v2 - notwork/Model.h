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
#include"models/plain.h"

class Model
{
public:
	Model(const float arr[], int size);
	Model(const char mod[]);
	void setPoint(const float arr[], int size);
	int drawModel();
	

private:
	GLuint VBO;
	GLuint VAO;
	int triangles;
};

