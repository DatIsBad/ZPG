#pragma once
#include<iostream>
#include<vector>

//to choose random model + random transformations
#include <cstdlib>
#include <ctime>

#include"ShaderProgram.h"
#include"Model.h"
#include"Transformation.h"
#include"Translate.h"
#include"Rotate.h"
#include"Scale.h"

class DrawableObject
{
public:
	DrawableObject(const char model[]);
	DrawableObject(const float model[], int size);
	~DrawableObject();
	int drawModels(ShaderProgram* shader);
	void addRotationModel(float angle, glm::vec3 rotation);
	void addScaleModel(glm::vec3 scaleValue);
	void addTranslationModel(glm::vec3 translation);

	int m_idShader;
private:
	Model* m_model;
	Transformation* m_translation;
};

