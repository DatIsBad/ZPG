#include "Scale.h"
Scale::Scale(float x, float y, float z) : scaleFactors(x,y,z){
	
}

glm::mat4 Scale::getValue()  {
	return glm::scale(glm::mat4(1.0f), scaleFactors);
}

void Scale::setScale(const glm::vec3& newScale) {
	scaleFactors = newScale;
}