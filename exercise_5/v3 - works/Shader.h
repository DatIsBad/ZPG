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

#include "ShaderProgram.h"
#include "Camera.h"
#include "Observer.h"

class Shader
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	Shader();
	Shader(int type);



	~Shader();
	void useShaderProgram();
	int checkShaderProgram();
	void useModelMatrix(glm::mat4 matrix); //for transformations
	void useViewMatrix(glm::mat4 viewMatrix);

private:
	void useMatrix4fv(const char* name, glm::mat4 value);
	void useVector3fv(const char* name, glm::vec3 value);

	const char* m_vertex_shader;
	const char* m_fragment_shader;
	GLuint m_shaderProgram;
	Camera* m_camera;

};

