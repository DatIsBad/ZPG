#include "ShaderProgram.h"
ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader) {
	m_shader = Shader(vertex_shader, fragment_shader);
	m_shaderProgram = glCreateProgram();
	m_shader.compileShader(m_shaderProgram);

	checkShaderProgram();
}

ShaderProgram::ShaderProgram() {
	m_shader = Shader();
	m_shaderProgram = glCreateProgram();
	m_shader.compileShader(m_shaderProgram);

	checkShaderProgram();
}

ShaderProgram::ShaderProgram(glm::vec3 color) {
	m_shader = Shader(color);
	m_shaderProgram = glCreateProgram();
	m_shader.compileShader(m_shaderProgram);

	checkShaderProgram();
}

ShaderProgram::ShaderProgram(int shaderType) {
	m_shader = Shader(shaderType);
	m_shaderProgram = glCreateProgram();
	m_shader.compileShader(m_shaderProgram);

	checkShaderProgram();
}

void ShaderProgram::useModelMatrix(glm::mat4 modelMatrix) {
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);

	/*
	printf("\n MODELMATRIX\n");
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			std::cout << modelMatrix[col][row] << " ";  // glm uses column-major order
		}
		std::cout << std::endl;
	}*/
}

void ShaderProgram::useViewMatrix(glm::mat4 viewMatrix) {
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);

	/*
	printf("\n VIEWMATRIX\n");
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			std::cout << viewMatrix[col][row] << " ";  // glm uses column-major order
		}
		std::cout << std::endl;
	}*/
}

void ShaderProgram::setMat4(const char* name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::useShaderProgram() {
	glUseProgram(m_shaderProgram);
	//checkShaderProgram();
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