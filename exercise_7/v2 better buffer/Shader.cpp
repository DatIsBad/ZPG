#include "Shader.h"
void Shader::defaultShader(GLuint shaderProgram) {
	loadShaders("shaders/VS_Default.glsl", "shaders/FS_Constant.glsl", shaderProgram);
}

void Shader::shaderLightConstant(GLuint shaderProgram) {
	loadShaders( "shaders/VS_Default.glsl", "shaders/FS_Constant.glsl", shaderProgram);
}

void Shader::shaderLightLambert(GLuint shaderProgram) {
	loadShaders("shaders/VS_Light.glsl", "shaders/FS_Lambert.glsl", shaderProgram);
	
}

void Shader::shaderLightPhong(GLuint shaderProgram) {
	loadShaders("shaders/VS_Light.glsl", "shaders/FS_Phong.glsl", shaderProgram);
}

void Shader::shaderLightBlinn(GLuint shaderProgram) {
	loadShaders("shaders/VS_Light.glsl", "shaders/FS_Blinn.glsl", shaderProgram);
}


//------------------------------------------------------------------------------------





void Shader::loadShaders(const std::string& vertexPath, const std::string& fragmentPath, GLuint shaderProgram) {
	// Read shader code from files
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	// Compile shaders
	GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

	// Link shaders into a program
	linkProgram(vertexShader, fragmentShader, shaderProgram);

	// Clean up shaders (no longer needed after linking)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

std::string Shader::readFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

// Compile a GLSL shader
GLuint Shader::compileShader(const std::string& source, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	const char* sourceCStr = source.c_str();
	glShaderSource(shader, 1, &sourceCStr, nullptr);
	glCompileShader(shader);

	// Check for compilation errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Error: Shader compilation failed ("
			<< (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
			<< ")\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}

	return shader;
}

// Link shaders into a program
void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint shaderProgram) {
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cerr << "Error: Program linking failed\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
}