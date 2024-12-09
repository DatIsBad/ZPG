#include "DrawableObject.h"

DrawableObject::DrawableObject() {
	m_model = new Model();
	m_idShader = 0;
}

DrawableObject::~DrawableObject() {
	delete m_model;

	for (Transformation* transl : m_tranl) {
		delete transl;  // Manually delete each allocated DrawableObject object
	}
}

void DrawableObject::addModel(const char model[]) {
	m_model->addModel(model);
	m_tranl.push_back(new Transformation());
}

void DrawableObject::addModel(const float model[], int size) {
	m_model->addModel(model, size);
	m_tranl.push_back(new Transformation());
}

void DrawableObject::drawModels(ShaderProgram* shader) {
	m_model->bind();
	for (int i = 0; i < m_model->getmodelCount(); i++) {
		shader->useModelMatrix(m_tranl.at(i)->getValue());
		m_model->drawModel( i );
	}
	m_model->unbind();
}


int DrawableObject::getmodelCount() {
	return m_model->getmodelCount();
}

void DrawableObject::addRotationModel(int id_model, float angle, glm::vec3 rotation) {
	m_tranl.at(id_model)->addTrans<Rotate>(angle, rotation);
	
	if (rand() % 6 == 0) {
		m_tranl.at(id_model)->makeMeRotateConst(m_tranl.at(id_model)->getSize() - 1);
	}
}

void DrawableObject::addScaleModel(int id_model, glm::vec3 scaleValue) {
	m_tranl.at(id_model)->addTrans<Scale>(scaleValue.x, scaleValue.y, scaleValue.z);
}

void DrawableObject::addTranslationModel(int id_model, glm::vec3 translation) {
	m_tranl.at(id_model)->addTrans<Translate>(translation.x, translation.y, translation.z);
}