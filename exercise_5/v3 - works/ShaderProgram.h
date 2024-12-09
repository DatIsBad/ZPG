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

class ShaderProgram
{
public:
	static void defaultShader(GLuint shaderProgram);

	static void shaderLightConstant(GLuint shaderProgram);
	static void shaderLightLambert(GLuint shaderProgram);
	static void shaderLightPhong(GLuint shaderProgram);
	static void shaderLightBlinn(GLuint shaderProgram);
private:
	static const char* defaultVertexShader();
	static const char* lightVertexShader();
	static const char* defaultFragmentShader();
	static const char* shaderLightConstant();

	static void compileShader(GLuint shaderProgram, const char* m_vertex_shader, const char* m_fragment_shader);

};

