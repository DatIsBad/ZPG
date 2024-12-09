#pragma once
//********************************************
// PHA0051
// 08/12/2024
//********************************************
// 
//Include GLM  
#include"Transformation.h"



class Scale : public Transformation
{
public:
	Scale(float x, float y, float z);
	glm::mat4 getValue()  override;
	void setScale(const glm::vec3& newScale);

private:
	glm::vec3 scaleFactors;
};

