#include "DrawableObject.h"

DrawableObject::DrawableObject(const char model[]) {
	m_model = new Model(model);
	m_translation = new Transformation();
	m_idShader = 0;
}

DrawableObject::DrawableObject(const float model[], int size) {
	m_model = new Model(model, size);
	m_translation = new Transformation();
}

DrawableObject::~DrawableObject() {
	delete m_model;
	delete m_translation;
}

int DrawableObject::drawModels(ShaderProgram* shader) {
	shader->useModelMatrix(m_translation->getValue());
	return m_model->drawModel();
}

void DrawableObject::addRotationModel(float angle, glm::vec3 rotation) {
	m_translation->addTrans<Rotate>(angle, rotation);
}

void DrawableObject::addScaleModel(glm::vec3 scaleValue) {
	m_translation->addTrans<Scale>(scaleValue.x, scaleValue.y, scaleValue.z);
}

void DrawableObject::addTranslationModel(glm::vec3 translation) {
	m_translation->addTrans<Translate>(translation.x, translation.y, translation.z);
}

