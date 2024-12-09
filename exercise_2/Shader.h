#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader();
	Shader(const char* vertex_shader, const char* fragment_shader);
	~Shader();
	void useShaderProgram();
	void checkShaderProgram();

private:
	const char* m_vertex_shader;
	const char* m_fragment_shader;
	GLuint m_shaderProgram;
};

