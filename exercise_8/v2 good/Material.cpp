#include "Material.h"

void Material::getMaterial(ShaderProgram* sh, int materialID) {
	if (materialID == 0) {	// metal
		sh->useMaterial(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.8f, 0.8f, 0.8f));
	}
	else if (materialID == 1) {	// wood
		sh->useMaterial(glm::vec3(0.3f, 0.2f, 0.1f), glm::vec3(0.5f, 0.3f, 0.2f), glm::vec3(0.1f, 0.05f, 0.02f));
	}
	else if (materialID == 2) {	// dirt
		sh->useMaterial(glm::vec3(0.2f, 0.15f, 0.1f), glm::vec3(0.4f, 0.3f, 0.2f), glm::vec3(0.05f, 0.05f, 0.05f));
	}
	else if (materialID == 3) {	// skin
		sh->useMaterial(glm::vec3(0.4f, 0.3f, 0.2f), glm::vec3(0.6f, 0.5f, 0.4f), glm::vec3(0.2f, 0.2f, 0.2f));
	}
}

int Material::getMaterialCount() {
	return 4;
}

