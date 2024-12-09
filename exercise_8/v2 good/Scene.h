#pragma once
#include<iostream>
#include<vector>
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Camera.h"
#include "Observer.h"
#include "LightGroup.h"
#include "Controller.h"
#include "TextureManager.h"

class Scene : public Observer
{
public:
	Scene(const Controller& controller);
	~Scene();
	int runScene();
	void addDOShader();
	void addDOShader(int type);
	void addDOShader(const char* vertex_shader, const char* fragment_shader);
	void addLight(int idDOShader, int type, bool isCamera, glm::vec3 lightPos, bool randomMovement);
	void addLight(int idDOShader, int type, bool isCamera, glm::vec3 lightPos, glm::vec3 color, bool randomMovement);
	void addLight(int idDOShader, int type, bool isCamera, glm::vec3 lightPos, glm::vec3 color, float intensity, float ambientStrength, float specularStrength, bool randomMovement);

	void addModel(int idDOShader, const char model[]);
	void addModel(int idDOShader, const float model[], int size);
	int getSizeDO(int idDOShader);
	void addRotationObjModel(int idDOShader, int moID, float angle, glm::vec3 rotation);
	void addScaleObjModel(int idDOShader, int moID, glm::vec3 scaleValue);
	void addTranslationObjModel(int idDOShader, int moID, glm::vec3 translation);
	void updateObservedKey(char userInput) ;
	void updateObservedCursor(double x, double y, bool locked);
	void makeLightMove(int id_lightgroup, int id_light);
	int getSizeLight(int idDOShader);
	void setLightAttenuation(int idDOShader, int lightID, float constant, float linear, float quadratic, float range);

	void prepareTextureManager();
	void prepareNightSky();
	void assignTexture(int idDOShader, int moID, std::string textureName, int textureMultiplier);



	void update() override;

	bool m_active;
private:
	std::vector<ShaderProgram*> m_shaders;
	std::vector<DrawableObject*> m_DObj;
	std::vector<LightGroup*> m_light;


	TextureManager* m_TextureMan;
	Camera* m_cam;
	float m_deltaTime;
	float m_lastFrame;
	double m_lastCursorX;
	double m_lastCursorY;

	int height_window;
	int width_window;
	bool cameraLocked;
	bool cameraFlashlight;


	const Controller& m_controller;
};

