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
	m_shaderProgram = glCreateProgram();
	ShaderProgram::defaultShader(m_shaderProgram);
}

Shader::Shader(int type) {
	m_shaderProgram = glCreateProgram();

	if (type == 0) {
		ShaderProgram::shaderLightConstant(m_shaderProgram);
	}
	else if (type == 1) {
		ShaderProgram::shaderLightLambert(m_shaderProgram);
	}
	else if (type == 2) {
		ShaderProgram::shaderLightPhong(m_shaderProgram);
	}
	else if (type == 3) {
		ShaderProgram::shaderLightBlinn(m_shaderProgram);
	}
	
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



// TODO make glGetUniformLocation local value; if its -1 it couldnt be found
void Shader::useModelMatrix(glm::mat4 matrix) {
	// Set up projection matrix (perspective)
	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(90.0f),  // Field of view
		1000.0f / 1000.0f,      // Aspect ratio
		0.1f,                 // Near clipping plane
		100.0f                // Far clipping plane
	);
	int val = 100;

	GLint projLoc = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	glm::vec3 colour = glm::vec3(0.5, 0.25, 0);
	glUniform3fv(glGetUniformLocation(m_shaderProgram, "colorConstant"), 1, &colour[0]);
	glUniformMatrix4fv( glGetUniformLocation(m_shaderProgram, "modelMatrix") , 1, GL_FALSE, &matrix[0][0]);
}

void Shader::useViewMatrix(glm::mat4 viewMatrix) {
	glm::mat4 invViewMatrix = inverse(viewMatrix); 
	glm::vec3 vecameraPos = glm::vec3(invViewMatrix[3]);

	useMatrix4fv("viewMatrix", viewMatrix);
	useVector3fv ("cameraPos", vecameraPos);

}


void Shader::useMatrix4fv(const char* name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}


void Shader::useVector3fv(const char* name, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(m_shaderProgram, name), 1, &value[0]);
}


