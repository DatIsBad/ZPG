#pragma once
#include<iostream>
#include<vector>
#include "Shader.h"
#include "DrawableObject.h"
#include "Camera.h"
#include "Observer.h"

class Scene : public Observer
{
public:
	Scene();
	~Scene();
	int runScene();
	void addDObjShaderOneColor();
	void addDObjShader();
	void addDObjShader(const char* vertex_shader, const char* fragment_shader);
	void addModel(int doID, int model);
	void addRotationObjModel(int doID, int moID, float angle, glm::vec3 rotation);
	void addScaleObjModel(int doID, int moID, glm::vec3 scaleValue);
	void addTranslationObjModel(int doID, int moID, glm::vec3 translation);
	void updateObservedKey(char userInput);
	void updateObservedCursor(double x, double y);

private:
	std::vector<Shader*> m_shaders;
	std::vector<DrawableObject*> m_DObj;
	Camera* m_cam;
	float m_deltaTime;
	float m_lastFrame;
	double m_lastCursorX;
	double m_lastCursorY;
};

