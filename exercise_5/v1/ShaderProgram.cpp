#include "ShaderProgram.h"
ShaderProgram::ShaderProgram() {
	m_shaderProgram = glCreateProgram();
	
	//TODO need to link verfrag
	//glLinkProgram(m_shaderProgram);
}



void ShaderProgram::useModelMatrix(glm::mat4 matrix) {
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "modelMatrix"), 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::useViewMatrix(glm::mat4 viewMatrix) {
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
}

void ShaderProgram::useShaderProgram() {
	glUseProgram(m_shaderProgram);
}

int ShaderProgram::checkShaderProgram() {
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