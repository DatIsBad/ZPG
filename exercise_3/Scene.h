#pragma once
#include<iostream>
#include<vector>
#include "Shader.h"
#include "DrawableObject.h"

class Scene
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


private:
	std::vector<Shader*> m_shaders;
	std::vector<DrawableObject*> m_DObj;
};

