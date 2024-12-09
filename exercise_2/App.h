#pragma once
#include <iterator> // for std::size()
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Controller.h"
#include "Buffer.h"
#include "Shader.h"

class App
{
public:
	App();
	~App();
	void RunApp();

private:
	GLFWwindow* m_window;
	Buffer* m_buffer;
	Shader* m_shader;

};

