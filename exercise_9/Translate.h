#pragma once
//********************************************
// PHA0051
// 08/12/2024
//********************************************
// 
//Include GLM  
#include"Transformation.h"

class Translate : public Transformation
{
public:
	Translate(float x, float y, float z);
	glm::mat4 getValue()  override;
	void setTranslation(const glm::vec3& newTranslation);

private:
	glm::vec3 translation;
};

