#include "DrawableObject.h"

DrawableObject::DrawableObject() {

}


DrawableObject::~DrawableObject() {
	for (Model* model : m_models) {
		delete model;  // Manually delete each allocated DrawableObject object
	}

	for (Transformation* trans : m_translations) {
		delete trans;  // Manually delete each allocated Transformation object
	}
}

void DrawableObject::addModel(int model) {
	if (model == 0) {
		m_models.push_back(new Model("bushes"));
	}
	else if (model == 1) {
		m_models.push_back(new Model("gift"));
	}
	else if (model == 2) {
		m_models.push_back(new Model("sphere"));
	}
	else if (model == 3) {
		m_models.push_back(new Model("tree"));
	}
	else if (model == 4) {
		m_models.push_back(new Model("suzi_flat"));
	}
	else if (model == 5) {
		m_models.push_back(new Model("suzi_smooth"));
	}

	m_translations.push_back(new Transformation());
}

int DrawableObject::drawModels(Shader* shader) {
	int check = 0;

	for (size_t i = 0; i < m_models.size(); ++i) {
		Model* mod = m_models[i];
		Transformation* trans = m_translations[i];

		check = mod->drawModel();
		shader->useShaderMatrix(trans->getValue());
		if (check == -1) break;
	}


	return check;
}

void DrawableObject::addRotationModel(int moID, float angle, glm::vec3 rotation) {
	Transformation* trans = m_translations[moID];
	trans->addTrans<Rotate>(angle, rotation);
}

void DrawableObject::addScaleModel(int moID, glm::vec3 scaleValue) {
	Transformation* trans = m_translations[moID];
	trans->addTrans<Scale>(scaleValue.x, scaleValue.y, scaleValue.z);
}

void DrawableObject::addTranslationModel(int moID, glm::vec3 translation) {
	Transformation* trans = m_translations[moID];
	trans->addTrans<Translate>(translation.x, translation.y, translation.z);
}