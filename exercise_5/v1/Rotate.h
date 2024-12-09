#pragma once
//Include GLM  
#include"Transformation.h"


class Rotate : public Transformation
{
public:
	Rotate(float angle, const glm::vec3& axis);	// angle example ... glm::radians(45.0f);   exis example ... glm::vec3(0.0f, 1.0f, 0.0f)
	glm::mat4 getValue() const override;

private:
	float angle;
	glm::vec3 axis;
};

