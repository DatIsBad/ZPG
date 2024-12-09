#include "Translate.h"
#include <glm/gtc/matrix_transform.hpp>

Translate::Translate(float x, float y, float z) : translation(x,y,z){
}

glm::mat4 Translate::getValue() const {
	return glm::translate(glm::mat4(1.0f), translation);
}