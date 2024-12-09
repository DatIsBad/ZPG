#include "Shader.h"

Shader::Shader(const char* vertex_shader, const char* fragment_shader) :
	m_vertex_shader(vertex_shader), m_fragment_shader(fragment_shader) {

	//create and compile shaders
	GLuint m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, &m_vertex_shader, NULL);
	glCompileShader(m_vertexShader);
	GLuint m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &m_fragment_shader, NULL);
	glCompileShader(m_fragmentShader);
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glAttachShader(m_shaderProgram, m_vertexShader);
	glLinkProgram(m_shaderProgram);

	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);
}

Shader::Shader() {
	m_vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 normal;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec3 color;"
		"void main () {"
		"     color = vp;"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"}";



	m_fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec3 color;"
		"void main () {"
		"   vec3 lightPosition = vec3 (10.0 ,10.0 ,10.0);"
		"	frag_colour = vec4 (color, 1.0);"
		"}";


	//create and compile shaders
	GLuint m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, &m_vertex_shader, NULL);
	glCompileShader(m_vertexShader);
	GLuint m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &m_fragment_shader, NULL);
	glCompileShader(m_fragmentShader);
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glAttachShader(m_shaderProgram, m_vertexShader);
	glLinkProgram(m_shaderProgram);

	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);
}


