#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	void useModelMatrix(glm::mat4 matrix); //for transformations
	void useViewMatrix(glm::mat4 viewMatrix);

	void useShaderProgram();
	int checkShaderProgram();

	


private:
	GLuint m_shaderProgram;
};

