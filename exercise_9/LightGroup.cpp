#include "LightGroup.h"
LightGroup::LightGroup() {

}
LightGroup::~LightGroup() {
	for (auto light : m_lights) {
		delete light; // Clean up each dynamically allocated Light
	}
	m_lights.clear();
}

void LightGroup::addLight(int type, bool isCamera, glm::vec3 position) {
	Light* newLight = new Light();     
	newLight->lightPos = position;     // Set position
	newLight->type = type;
	newLight->isCamera = isCamera;
	m_lights.push_back(newLight);
}

void LightGroup::addLight(int type, bool isCamera, glm::vec3 position, glm::vec3 color) {
	Light* newLight = new Light();
	newLight->lightPos = position;
	newLight->lightColor = color;
	newLight->type = type;
	newLight->isCamera = isCamera;
	m_lights.push_back(newLight);
}

void LightGroup::addLight(int type, bool isCamera, glm::vec3 position, glm::vec3 color, float intensity, float ambientStrength, float specularStrength) {
	Light* newLight = new Light();
	newLight->lightPos = position;
	newLight->lightColor = color;
	newLight->lightIntensity = intensity;
	newLight->ambientStrength = ambientStrength;
	newLight->specularStrength = specularStrength;
	newLight->type = type;
	newLight->isCamera = isCamera;
	m_lights.push_back(newLight);
}

void LightGroup::updateAll(ShaderProgram* shad) {
	shad->useLightCount(m_lights.size());

	for (int i = 0; i < m_lights.size(); i++) {
		if (m_lights[i]->random == true) {
			m_lights[i]->lightPos = glm::vec3(m_lights[i]->lightPos.x + (rand() % 11 - 5.0) / 50.0, m_lights[i]->lightPos.y, m_lights[i]->lightPos.z + (rand() % 11 - 5.0) / 50.0);
		}

		std::string baseName = "lights[" + std::to_string(i) + "]";
		shad->useLightShader(baseName, m_lights[i]->lightPos, m_lights[i]->lightColor, m_lights[i]->lightIntensity, m_lights[i]->ambientStrength, m_lights[i]->specularStrength, 
			m_lights[i]->constant, m_lights[i]->linear, m_lights[i]->quadratic, m_lights[i]->range,
			m_lights[i]->type, m_lights[i]->lightDir, m_lights[i]->innerCutoff, m_lights[i]->outerCutoff, m_lights[i]->enabled, m_lights[i]->isCamera);
	}
}

void LightGroup::randMovement(int at) {
	m_lights[at]->random = true;
}

int LightGroup::getSize() {
	return m_lights.size();
}

void LightGroup::setPos(int at, glm::vec3 pos) {
	m_lights[at]->lightPos = pos;
}

void LightGroup::setLightCone(int at, glm::vec3 lightDir, float innerCutoff, float outerCutoff) {
	m_lights[at]->lightDir = lightDir;

	if (innerCutoff > 0) {
		m_lights[at]->innerCutoff = glm::cos(glm::radians(innerCutoff));
		m_lights[at]->outerCutoff = glm::cos(glm::radians(outerCutoff));
	}
	
}

void LightGroup::setLightModel(int at, Transformation* trans) {
	trans->changeTranslation(0, m_lights[at]->lightPos);
}

void LightGroup::setAttenuation(int at, float constant, float linear, float quadratic, float range) {
	if (constant >= 0)
		m_lights[at]->constant = constant;
	if (linear >= 0)
		m_lights[at]->linear = linear;
	if (quadratic >= 0)
		m_lights[at]->quadratic = quadratic;
	if (range >= 0)
		m_lights[at]->range = range;
}


void LightGroup::disableLight(int at) {
	if (at < 0 || at >= m_lights.size()) {
		return;
	}

	m_lights[at]->enabled = false;
}

void LightGroup::enableLight(int at) {
	if (at < 0 || at >= m_lights.size()) {
		return;
	}

	m_lights[at]->enabled = true;
}

void LightGroup::disableCameraLight() {
	for (int i = 0; i < m_lights.size(); i++) {
		if (m_lights[i]->isCamera == true) {
			m_lights[i]->enabled = false;
		}
	}
}

void LightGroup::enableCameraLight() {
	for (int i = 0; i < m_lights.size(); i++) {
		if (m_lights[i]->isCamera == true) {
			m_lights[i]->enabled = true;
		}
	}
}