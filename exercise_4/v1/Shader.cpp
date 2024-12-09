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

Shader::Shader(glm::vec3 colour) {
	m_vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec3 worldNorm;"
		"void main () {"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"}";



	std::string helper =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vec4 ("
		+ std::to_string(colour.x) + ", " + std::to_string(colour.y) + ", " + std::to_string(colour.z) + ", 1.0);"
		"}";

	m_fragment_shader = helper.c_str();



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
}

Shader::~Shader() {

}

void Shader::useShaderProgram() {
	glUseProgram(m_shaderProgram);
}

int Shader::checkShaderProgram() {
	GLint status;
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(m_shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;

		return -1;
	}

	return 1;
}

void Shader::useShaderMatrix(glm::mat4 matrix) {
	// Set up projection matrix (perspective)
	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(45.0f),  // Field of view
		800.0f / 600.0f,      // Aspect ratio
		0.1f,                 // Near clipping plane
		100.0f                // Far clipping plane
	);
	int val = 100;

	GLint projLoc = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	glUniformMatrix4fv( glGetUniformLocation(m_shaderProgram, "modelMatrix") , 1, GL_FALSE, &matrix[0][0]);
}

void Shader::useViewMatrix(glm::mat4 viewMatrix) {
	glUniformMatrix4fv(  glGetUniformLocation(m_shaderProgram, "viewMatrix")  , 1, GL_FALSE, &viewMatrix[0][0]);
}


