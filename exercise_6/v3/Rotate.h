#pragma once
//Include GLM  
#include"Transformation.h"


class Rotate : public Transformation
{
public:
	Rotate(float angle, const glm::vec3& axis);	// angle example ... glm::radians(45.0f);   exis example ... glm::vec3(0.0f, 1.0f, 0.0f)
	glm::mat4 getValue() override;
	void setRotation(float newAngle, const glm::vec3& newAxis);
	void dynamicRotationActivate();

private:
	bool dynamicRotation;
	float angle;
	glm::vec3 axis;
};

