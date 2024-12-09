#include "Scale.h"
Scale::Scale(float x, float y, float z) : scaleFactors(x,y,z){
	
}

glm::mat4 Scale::getValue() const {
	return glm::scale(glm::mat4(1.0f), scaleFactors);
}