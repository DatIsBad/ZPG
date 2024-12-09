#include "Shader.h"

Shader::Shader(const char* vertex_shader, const char* fragment_shader) :
	m_vertex_shader(vertex_shader), m_fragment_shader(fragment_shader) {

}

Shader::Shader() {
	defaultVertexShader();
	defaultFragmentShader();
}

Shader::Shader(glm::vec3 color) {
	defaultVertexShader();
	defaultFragmentShader(color);
	
}

Shader::Shader(int type) {
	if(type == 0) {
		shaderLightConstant();
	}
	else if (type == 1) {
		shaderLightLambert();
	}
	else if (type == 2) {
		shaderLightPhong();
	}
	else if (type == 3) {
		shaderLightBlinn();
	}

}

Shader::~Shader() {
	
}

void Shader::compileShader(GLuint shaderProgram) {
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

//-------------------------------------------------------------------------------------------------------------

void Shader::defaultVertexShader() {
	m_vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 normal;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"out vec3 color;"
		"void main () {"
		"     color = vp;"
		"     gl_Position = viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"}";
}

void Shader::lightVertexShader() {
	m_vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vn;"

		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"

		"out vec4 worldPos;"
		"out vec3 worldNorm;"

		"void main () {"
		"     worldPos = modelMatrix * vec4 ( vp ,1.0);"
		"     mat4 normal = modelMatrix;"
		"     worldNorm = vec3 ( normal * vec4 ( vn ,1.0));"
		"     gl_Position = viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"}";
}

void Shader::defaultFragmentShader() {
	m_fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec3 color;"
		"void main () {"
		"	frag_colour = vec4 (color, 1.0);"
		"}";

}

void Shader::defaultFragmentShader(glm::vec3 color) {
	std::string helper =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vec4 ("
		+ std::to_string(color.x) + ", " + std::to_string(color.y) + ", " + std::to_string(color.z) + ", 1.0);"
		"}";

	m_fragment_shader = helper.c_str();
}


//-------------------------------------------------------------------------------------------------------------

void Shader::shaderLightConstant() {
	defaultVertexShader();
	defaultFragmentShader(glm::vec3(0.385, 0.647, 0.812));
}

void Shader::shaderLightLambert() {
	lightVertexShader();

	m_fragment_shader =
		"#version 330\n"
		"in vec4 worldPos;"
		"in vec3 worldNorm;"

		"out vec4 frag_colour;"

		"void main () {"
		"   vec3 lightPosition = vec3 (10.0 ,10.0 ,10.0);"
		"   vec3 lightColor = vec3 (1.0 , 1.0 ,0.5);"
		"   vec3 modelColor = vec3 (0.385 ,0.647 ,0.812);"
		"   vec3 fragPos = worldPos.xyz;"
		"   vec3 view = viewMatrix.xyz;"

		// cal diffuse
		"   vec3 norm = normalize(worldNorm);"
		"   vec3 lightDir = normalize(lightPosition - fragPos);"
		"   float diff = max(dot(norm, lightDir), 0.0);"
		"   vec3 diffuse = diff * lightColor;"

		// result
		"   vec3 result = diffuse * objectColor;"
		"   FragColor = vec4(result, 1.0);"
		"}";
}

void Shader::shaderLightPhong() {
	lightVertexShader();

	m_fragment_shader =
		"#version 330\n"
		"in vec4 worldPos;"
		"in vec3 worldNorm;"

		"uniform mat4 viewMatrix;"

		"out vec4 frag_colour;"

		"void main () {"
		"   vec3 lightPosition = vec3 (10.0 ,10.0 ,10.0);"
		"   vec3 lightColor = vec3 (1.0 , 1.0 ,0.5);"
		"   vec3 modelColor = vec3 (0.385 ,0.647 ,0.812);"
		"   vec3 fragPos = worldPos.xyz;"
		"   vec3 view = viewMatrix.xyz;"

		// Ambient component
		"   float ambientStrength = 0.1;"
		"   vec3 ambient = ambientStrength * lightColor;"

		// cal diffuse
		"   vec3 norm = normalize(worldNorm);"
		"   vec3 lightDir = normalize(lightPosition - fragPos);"
		"   float diff = max(dot(norm, lightDir), 0.0);"
		"   vec3 diffuse = diff * lightColor;"

		// cal specular
		"   vec3 viewDir = normalize(view - fragPos);"
		"   vec3 reflectDir = reflect ( - lightDir , norm );"
		"   float spec = pow ( max ( dot ( viewDir , reflectDir ))0.0) ,32);"
		"   vec3 specular = spec * lightColor;"

		// result
		"   vec3 result = (ambient + diffuse + specular) * modelColor;"
		"   frag_colour = vec4 (result, 1.0f);"
		"}";
}

void Shader::shaderLightBlinn() {
	lightVertexShader();

	m_fragment_shader =
		"#version 330\n"
		"in vec4 worldPos;"
		"in vec3 worldNorm;"

		"uniform mat4 viewMatrix;"

		"out vec4 frag_colour;"

		"void main () {"
		"   vec3 lightPosition = vec3 (10.0 ,10.0 ,10.0);"
		"   vec3 lightColor = vec3 (1.0 , 1.0 ,0.5);"
		"   vec3 modelColor = vec3 (0.385 ,0.647 ,0.812);"
		"   vec3 fragPos = worldPos.xyz;"
		"   vec3 view = viewMatrix.xyz;"

		// Ambient component
		"   float ambientStrength = 0.1;"
		"   vec3 ambient = ambientStrength * lightColor;"

		// cal diffuse
		"   vec3 norm = normalize(worldNorm);"
		"   vec3 lightDir = normalize(lightPosition - fragPos);"
		"   float diff = max(dot(norm, lightDir), 0.0);"
		"   vec3 diffuse = diff * lightColor;"

		// cal specular
		"   vec3 viewDir = normalize(view - fragPos);"
		"   vec3 halfwayDir = normalize(lightDir + viewDir);"
		"   float spec = pow ( max ( dot ( viewDir , halfwayDir ))0.0) ,32);"
		"   vec3 specular = spec * lightColor;"

		// result
		"   vec3 result = (ambient + diffuse + specular) * modelColor;"
		"   frag_colour = vec4 (result, 1.0f);"
		"}";
}