#include "Rotate.h"

Rotate::Rotate(float angle, const  glm::vec3& axis) : angle(angle), axis(axis) {	// angle example ... glm::radians(45.0f);   exis example ... glm::vec3(0.0f, 1.0f, 0.0f)
	printf("ROTATE ");
}

glm::mat4 Rotate::getValued() const {
	return glm::rotate(glm::mat4(1.0f), angle, axis);
}