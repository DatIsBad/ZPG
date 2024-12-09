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
#include"TextureManager.h"

class DrawableObject
{
public:
	DrawableObject();
	~DrawableObject();
	void addModel(const char model[]);
	void addModel(const float model[], int size);
	void drawModels(ShaderProgram* shader, TextureManager* texture);
	void assignTexture(int id_model, std::string textureName, int textureMultiplier);


	int getmodelCount();
	void addRotationModel(int id_model, float angle, glm::vec3 rotation);
	void addScaleModel(int id_model, glm::vec3 scaleValue);
	void addTranslationModel(int id_model, glm::vec3 translation);


	int m_idShader;
private:
	Model* m_model;
	std::vector<Transformation*> m_tranl;
};

