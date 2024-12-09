#pragma once
#include <vector>
#include <cstdlib>
#include"ShaderProgram.h"
#include"Transformation.h"

struct Light {
	glm::vec3 lightPos;
	glm::vec3 lightColor = glm::vec3(1.0, 1.0, 0.5);
	float lightIntensity = 1.0f;
	float ambientStrength = 0.05f;
	float specularStrength = 0.5f;
	bool random = false;

	float constant = 1.0f;		// Constant attenuation (range of unafection)
	float linear = 0.09f;		// Linear attenuation
	float quadratic = 0.032f;	// Quadratic attenuation
	float range = 5.0f;			// Light cutoff range
};

class LightGroup
{
public:
	LightGroup();
	~LightGroup();
	void addLight(glm::vec3 position);
	void addLight(glm::vec3 position, glm::vec3 color);
	void addLight(glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, float specularStrength);

	void updateAll(ShaderProgram* shad);
	void randMovement(int at);
	int getSize();
	void setPos(int at, glm::vec3 pos);
	void setLightModel(int at, Transformation* trans);

private:
	std::vector<Light*> m_lights;
};

