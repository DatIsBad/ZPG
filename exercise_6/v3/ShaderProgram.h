#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <string>

#include "Shader.h"
#include "Camera.h"
#include "Observer.h"

class ShaderProgram : public Observer
{
public:
	ShaderProgram(const char* vertex_shader, const char* fragment_shader, const Camera& cam);
	ShaderProgram(const Camera& cam);
	ShaderProgram(int type, const Camera& cam);
	~ShaderProgram();

	void useShaderProgram();
	int checkShaderProgram();

	void useModelMatrix(glm::mat4 matrix); //for transformations
	void useLightCount(int num);
	void useLightShader(std::string baseName, glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, float specularStrength, float constant, float linear, float quadratic, float range);


	//OBSERVER
	void update() override;

private:
	void useMatrix4fv(const char* name, glm::mat4 value);
	void useVector3fv(const char* name, glm::vec3 value);
	void useFloat(const char* name, float value);

	

	const char* m_vertex_shader;
	const char* m_fragment_shader;
	GLuint m_shaderProgram;
	const Camera& m_camera;

	GLint viewLoc;
	GLint projLoc;
	GLint cposLoc;
};

