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
	ShaderProgram(const char* vertex_shader, const char* fragment_shader);
	ShaderProgram();
	ShaderProgram(glm::vec3 color);
	ShaderProgram(int shaderType);

	void useModelMatrix(glm::mat4 modelMatrix); //transformation
	void useViewMatrix(glm::mat4 viewMatrix); //camera
	void setMat4(const char* name, glm::mat4 value);

	void useShaderProgram();
	int checkShaderProgram();

	


private:
	Shader m_shader;
	GLuint m_shaderProgram;
};

