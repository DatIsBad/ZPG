#pragma once
//********************************************
// PHA0051
// 08/12/2024
//********************************************

#include <stdio.h>
#include <fstream>
#include <sstream>
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

class Shader
{
public:
	static void defaultShader(GLuint shaderProgram);
	static void shaderLightConstant(GLuint shaderProgram);
	static void shaderLightLambert(GLuint shaderProgram);
	static void shaderLightPhong(GLuint shaderProgram);
	static void shaderLightBlinn(GLuint shaderProgram);
	static void shaderCubeMap(GLuint shaderProgram);

private:
	static void loadShaders(const std::string& vertexPath, const std::string& fragmentPath, GLuint shaderProgram);
	static std::string readFile(const std::string& filePath);
	static GLuint compileShader(const std::string& source, GLenum shaderType);
	static void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint shaderProgram);
};

