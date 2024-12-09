#pragma once
#include<iostream>
#include<vector>

//to choose random model + random transformations
#include <cstdlib>
#include <ctime>

#include"Shader.h"
#include"Model.h"
#include"Transformation.h"
#include"Translate.h"
#include"Rotate.h"
#include"Scale.h"

class DrawableObject
{
public:
	DrawableObject();
	~DrawableObject();
	void addModel(int model);	// 0 - bush; 1 - gift; 2 - sphere; 3 - tree; 4 - suzi_flat; 5 - suzi_smooth
	int drawModels(Shader* shader);
	void addRotationModel(int moID, float angle, glm::vec3 rotation);
	void addScaleModel(int moID, glm::vec3 scaleValue);
	void addTranslationModel(int moID, glm::vec3 translation);


private:
	std::vector<Model*> m_models;
	std::vector<Transformation*> m_translations;
};

