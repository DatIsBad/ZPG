#pragma once
#include <vector>
#include <cstdlib>
#include"ShaderProgram.h"
#include"Transformation.h"


struct Light {
	glm::vec3 lightPos = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 lightColor = glm::vec3(1.0, 1.0, 0.5);
	float lightIntensity = 0.95f;
	float ambientStrength = 0.05f;
	float specularStrength = 0.5f;
	bool random = false;

	float constant = 1.0f;		// Constant attenuation (range of unafection)
	float linear = 0.09;		// Linear attenuation
	float quadratic = 0.034f;	// Quadratic attenuation
	float range = 10.0f;			// Light cutoff range

	int type = 0;		// type: 0 = point; 1 = cone; 2 = directional
	glm::vec3 lightDir = glm::vec3(-2.0, -8.0, -2.0);		// Light direction for directional lights
	float innerCutoff = glm::cos(glm::radians(10.5f));		// Inner cutoff for cone light
	float outerCutoff = glm::cos(glm::radians(20.5f));		// Outer cutoff for cone light

	bool enabled = true;	// if the light should be currently active
	bool isCamera = false;	// if it's attached to camera
};

class LightGroup
{
public:
	LightGroup();
	~LightGroup();
	void addLight(int type, bool isCamera, glm::vec3 position);
	void addLight(int type, bool isCamera, glm::vec3 position, glm::vec3 color);
	void addLight(int type, bool isCamera, glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, float specularStrength);

	void updateAll(ShaderProgram* shad);
	void randMovement(int at);
	int getSize();
	void setPos(int at, glm::vec3 pos);
	void setLightDir(int at, glm::vec3 lightDir);
	void setLightModel(int at, Transformation* trans);
	void setAttenuation(int at, float constant, float linear, float quadratic, float range);

	void disableLight(int at);
	void enableLight(int at);
	void disableCameraLight();
	void enableCameraLight();

private:
	std::vector<Light*> m_lights;
};

