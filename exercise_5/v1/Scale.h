#pragma once
//Include GLM  
#include"Transformation.h"



class Scale : public Transformation
{
public:
	Scale(float x, float y, float z);
	glm::mat4 getValue() const override;
private:
	glm::vec3 scaleFactors;
};

