#include "ShaderProgram.h"
void ShaderProgram::defaultShader(GLuint shaderProgram) {
	compileShader(shaderProgram, defaultVertexShader(), defaultFragmentShader());
}

void ShaderProgram::shaderLightConstant(GLuint shaderProgram) {
	compileShader(shaderProgram, defaultVertexShader(), shaderLightConstant());
}

void ShaderProgram::shaderLightLambert(GLuint shaderProgram) {
	const char* m_fragment_shader =
		"#version 330 core\n"
		"in vec4 worldPos;"
		"in vec3 worldNorm;"
		"out vec4 frag_colour;"
		"void main () {"
		"   vec3 lightPosition = vec3 (0.0f ,0.0f , 0.0f);"
		"   vec3 lightColor = vec3 (1.0 , 1.0 ,0.5);"
		"   vec3 modelColor = vec3 (0.385f ,0.647f ,0.812f);"
		"   vec3 fragPos = worldPos.xyz;"
		// cal diffuse
		"   vec3 norm = normalize(worldNorm);"
		"   vec3 lightDir = normalize(lightPosition - fragPos);"
		"   float diff = max(dot(norm, lightDir), 0.0);"
		"   vec3 diffuse = diff * lightColor;"
		// result
		"   vec3 result = diffuse * modelColor;"
		"   frag_colour = vec4(result, 1.0);"
		"}";
	compileShader(shaderProgram, lightVertexShader(), m_fragment_shader);
}

void ShaderProgram::shaderLightPhong(GLuint shaderProgram) {
	const char* m_fragment_shader =
		"#version 330\n"
		"in vec4 worldPos;"
		"in vec3 worldNorm;"
		"uniform vec3 cameraPos;"
		"out vec4 frag_colour;"
		"void main () {"
		"   vec3 lightPosition = vec3 (0.0 ,0.0 ,0.0);"
		"   vec3 lightColor = vec3 (1.0 , 1.0 ,0.5);"
		"   vec3 modelColor = vec3 (0.385 ,0.647 ,0.812);"
		"   vec3 fragPos = worldPos.xyz;"
		// Ambient component
		"   float ambientStrength = 0.1;"
		"   vec3 ambient = ambientStrength * lightColor;"
		// cal diffuse
		"   vec3 norm = normalize(worldNorm);"
		"   vec3 lightDir = normalize(lightPosition - fragPos);"
		"   float diff = max(dot(norm, lightDir), 0.0);"
		"   vec3 diffuse = diff * lightColor;"
		// cal specular
		"   vec3 viewDir = normalize(cameraPos - fragPos);"
		"   vec3 reflectDir = reflect ( - lightDir , norm );"
		"   float spec = pow ( max ( dot ( viewDir , reflectDir ),0.0) ,32);"
		"   vec3 specular = spec * lightColor;"
		// result
		"   vec3 result = (ambient + diffuse + specular) * modelColor;"
		"   frag_colour = vec4 (result, 1.0f);"
		"}";
	compileShader(shaderProgram, lightVertexShader(), m_fragment_shader);
}

void ShaderProgram::shaderLightBlinn(GLuint shaderProgram) {
	const char* m_fragment_shader =
		"#version 330\n"
		"in vec4 worldPos;"
		"in vec3 worldNorm;"
		"uniform vec3 cameraPos;"
		"out vec4 frag_colour;"
		"void main () {"
		"   vec3 lightPosition = vec3 (0.0 ,0.0 ,0.0);"
		"   vec3 lightColor = vec3 (1.0 , 1.0 ,0.5);"
		"   vec3 modelColor = vec3 (0.385 ,0.647 ,0.812);"
		"   vec3 fragPos = worldPos.xyz;"
		// Ambient component
		"   float ambientStrength = 0.1;"
		"   vec3 ambient = ambientStrength * lightColor;"
		// cal diffuse
		"   vec3 norm = normalize(worldNorm);"
		"   vec3 lightDir = normalize(lightPosition - fragPos);"
		"   float diff = max(dot(norm, lightDir), 0.0);"
		"   vec3 diffuse = diff * lightColor;"
		// cal specular
		"   vec3 viewDir = normalize(cameraPos - fragPos);"
		"   vec3 halfwayDir = normalize(lightDir + viewDir);"
		"   float spec = pow ( max ( dot ( norm , halfwayDir ),0.0) ,32);"
		"   vec3 specular = spec * lightColor;"
		// result
		"   vec3 result = (ambient + diffuse + specular) * modelColor;"
		"   frag_colour = vec4 (result, 1.0f);"
		"}";
	compileShader(shaderProgram, lightVertexShader(), m_fragment_shader);
}



//------------------------------------------------------------------------------------
const char* ShaderProgram::defaultVertexShader() {
	const char* m_vertex_shader =
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

	return m_vertex_shader;
}

const char* ShaderProgram::lightVertexShader() {
	const char* m_vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vn;"

		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec4 worldPos;"
		"out vec3 worldNorm;"

		"void main () {"
		"     worldPos = modelMatrix * vec4 ( vp ,1.0);"
		"    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));"
		"    worldNorm = normalize(normalMatrix * vn);"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"}";

	return m_vertex_shader;
}

const char* ShaderProgram::defaultFragmentShader() {
	const char* m_fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec3 color;"
		"void main () {"
		"	frag_colour = vec4 (color, 1.0);"
		"}";

	return m_fragment_shader;
}

const char* ShaderProgram::shaderLightConstant() {
	const char* m_fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec3 color;"
		"uniform vec3 colorConstant;"
		"void main () {"
		"	frag_colour = vec4 (colorConstant, 1.0);"
		"}";

	return m_fragment_shader;
}




//------------------------------------------------------------------------------------
void ShaderProgram::compileShader(GLuint shaderProgram, const char* m_vertex_shader, const char* m_fragment_shader) {
	//create and compile shaders
	GLuint m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, &m_vertex_shader, NULL);
	glCompileShader(m_vertexShader);
	GLuint m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &m_fragment_shader, NULL);
	glCompileShader(m_fragmentShader);
	
	glAttachShader(shaderProgram, m_fragmentShader);
	glAttachShader(shaderProgram, m_vertexShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);
}