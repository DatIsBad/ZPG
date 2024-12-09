#pragma once
#include<iostream>
#include<vector>
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Camera.h"
#include "Observer.h"

class Scene : public Observer
{
public:
	Scene();
	~Scene();
	void runScene();
	void addShaderOneColor();
	void addShaderOneColor(float R, float G, float B);
	void addShader();
	void addShader(const char* vertex_shader, const char* fragment_shader);
	void addModel(const char model[], int IdShader);
	void addModel(const float model[], int size, int IdShader);
	void addRotationObjModel(int moID, float angle, glm::vec3 rotation);
	void addScaleObjModel(int moID, glm::vec3 scaleValue);
	void addTranslationObjModel(int moID, glm::vec3 translation);
	void updateObservedKey(char userInput);
	void updateObservedCursor(double x, double y);


private:
	std::vector<ShaderProgram*> m_shaders;
	std::vector<DrawableObject*> m_DObj;
	Camera* m_cam;
	float m_deltaTime;
	float m_lastFrame;
	double m_lastCursorX;
	double m_lastCursorY;
};

