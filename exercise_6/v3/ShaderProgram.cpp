#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader, const Camera& cam) :
	m_vertex_shader(vertex_shader), m_fragment_shader(fragment_shader), m_camera(cam) {

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

	const_cast<Camera&>(m_camera).addObserver(this);
	viewLoc = glGetUniformLocation(m_shaderProgram, "viewMatrix");
	projLoc = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	cposLoc = glGetUniformLocation(m_shaderProgram, "cameraPos");
}

ShaderProgram::ShaderProgram(const Camera& cam) :
	m_camera(cam) {
	m_shaderProgram = glCreateProgram();
	Shader::defaultShader(m_shaderProgram);

	const_cast<Camera&>(m_camera).addObserver(this);
	viewLoc = glGetUniformLocation(m_shaderProgram, "viewMatrix");
	projLoc = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	cposLoc = glGetUniformLocation(m_shaderProgram, "cameraPos");
}

ShaderProgram::ShaderProgram(int type, const Camera& cam):
	m_camera(cam) {
	m_shaderProgram = glCreateProgram();

	if (type == 0) {
		Shader::shaderLightConstant(m_shaderProgram);
	}
	else if (type == 1) {
		Shader::shaderLightLambert(m_shaderProgram);
	}
	else if (type == 2) {
		Shader::shaderLightPhong(m_shaderProgram);
	}
	else if (type == 3) {
		Shader::shaderLightBlinn(m_shaderProgram);
	}

	const_cast<Camera&>(m_camera).addObserver(this);
	viewLoc = glGetUniformLocation(m_shaderProgram, "viewMatrix");
	projLoc = glGetUniformLocation(m_shaderProgram, "projectionMatrix");
	cposLoc = glGetUniformLocation(m_shaderProgram, "cameraPos");
}

ShaderProgram::~ShaderProgram() {
	const_cast<Camera&>(m_camera).removeObserver(this);
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



// TODO make glGetUniformLocation local value; if its -1 it couldnt be found
void ShaderProgram::useModelMatrix(glm::mat4 matrix) {
	glm::vec3 colour = glm::vec3(0.5, 0.25, 0);
	glUniform3fv(glGetUniformLocation(m_shaderProgram, "colorConstant"), 1, &colour[0]);
	glUniformMatrix4fv( glGetUniformLocation(m_shaderProgram, "modelMatrix") , 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::useLightCount(int num) {
	glUniform1i(glGetUniformLocation(m_shaderProgram, "numLights"), num);
}



void ShaderProgram::useLightShader(std::string baseName, glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, float specularStrength, float constant, float linear, float quadratic, float range) {
	useVector3fv((baseName + ".lightPos").c_str(), position);
	useVector3fv((baseName + ".lightColor").c_str(), color);
	useFloat((baseName + ".lightIntensity").c_str(), intensity);
	useFloat((baseName + ".ambientStrength").c_str(), ambientStrength);
	useFloat((baseName + ".specularStrength").c_str(), specularStrength);
	useFloat((baseName + ".constant").c_str(), constant);
	useFloat((baseName + ".linear").c_str(), linear);
	useFloat((baseName + ".quadratic").c_str(), quadratic);
	useFloat((baseName + ".range").c_str(), range);
}






void ShaderProgram::useMatrix4fv(const char* name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name), 1, GL_FALSE, &value[0][0]);
}


void ShaderProgram::useVector3fv(const char* name, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(m_shaderProgram, name), 1, &value[0]);
}

void ShaderProgram::useFloat(const char* name, float value) {
	glUniform1f(glGetUniformLocation(m_shaderProgram, name), value);
}



void ShaderProgram::update() {
	useShaderProgram();
	glm::mat4 viewMatrix =	glm::make_mat4(glm::value_ptr(m_camera.GetViewMatrix()));
	glm::mat4 projectionMatrix = glm::make_mat4(glm::value_ptr(m_camera.GetProjectionMatrix()));
	glm::vec3 cameraPosition = m_camera.GetCameraPos();

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3fv(cposLoc, 1, &cameraPosition[0]);


	
}




