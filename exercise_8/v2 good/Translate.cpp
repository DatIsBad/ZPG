#include "Translate.h"
#include <glm/gtc/matrix_transform.hpp>

Translate::Translate(float x, float y, float z) : translation(x,y,z){
}

glm::mat4 Translate::getValue()  {
	return glm::translate(glm::mat4(1.0f), translation);
}

void Translate::setTranslation(const glm::vec3& newTranslation) {
	translation = newTranslation;
}