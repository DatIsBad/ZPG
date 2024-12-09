#include "Scene.h"

Scene::Scene() {
	//m_model = new Model("sphere");
	std::srand(std::time(nullptr));	//current time is seed
	addShader();
	m_cam = new Camera();
	m_lastCursorX = 0;
	m_lastCursorY = 0;
}

Scene::~Scene() {
	for (Shader* shader : m_shaders) {
		delete shader;  // Manually delete each allocated Shader object
	}

	for (DrawableObject* m_dobj : m_DObj) {
		delete m_dobj;  // Manually delete each allocated DrawableObject object
	}
	delete m_cam;
}

int Scene::runScene() {
	//get deltaTime
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;

	//draw all models
	for (size_t i = 0; i < m_shaders.size(); i++) {
		Shader* shader = m_shaders[i];

		shader->useShaderProgram();
		shader->useViewMatrix(m_cam->GetViewMatrix());

		for (size_t k = 0; k < m_DObj.size(); k++) {
			DrawableObject* DObj = m_DObj[k];
			
			if (DObj->m_idShader == i) {
				DObj->drawModels(shader);
			}
		}
	}

	//check for shader errors
	for (Shader* shader : m_shaders) {
		// Access each Shader* in the vector
		if (shader->checkShaderProgram() == -1)
		{
			return -1;
		}
	}


	return 1;
}

void Scene::addShaderOneColor() {
	m_shaders.push_back(new Shader(glm::vec3( (float)(std::rand() % 100) / (float)100, (float)(std::rand() % 100) / (float)100, (float)(std::rand() % 100) / (float)100) ));
}

void Scene::addShaderOneColor(float R, float G, float B) {
	m_shaders.push_back(new Shader( glm::vec3(R, G, B) ));
}

void Scene::addShader() {
	m_shaders.push_back(new Shader());
}

void Scene::addShader(const char* vertex_shader, const char* fragment_shader) {
	m_shaders.push_back(new Shader(vertex_shader, fragment_shader));
}

void Scene::addModel(const char model[], int IdShader) { //choose model
	m_DObj.push_back(new DrawableObject(model));
	m_DObj.at(m_DObj.size() - 1)->m_idShader = IdShader;
}

void Scene::addModel(const float model[], int size, int IdShader) { //choose model
	m_DObj.push_back(new DrawableObject(model, size));
	m_DObj.at(m_DObj.size() - 1)->m_idShader = IdShader;
}

void Scene::addRotationObjModel(int moID, float angle, glm::vec3 rotation) {
	m_DObj.at(moID)->addRotationModel(angle, rotation);
}

void Scene::Scene::addScaleObjModel(int moID, glm::vec3 scaleValue) {
	m_DObj.at(moID)->addScaleModel(scaleValue);
}


void Scene::addTranslationObjModel(int moID, glm::vec3 translation) {
	m_DObj.at(moID)->addTranslationModel(translation);
}

void Scene::updateObservedKey(char userInput) {
	m_cam->ProcessKeyboard(userInput, m_deltaTime);
}

void Scene::updateObservedCursor(double x, double y) {
	float xtemp = x - m_lastCursorX;
	float ytemp = m_lastCursorY - y;

	printf("%f %f\n", xtemp, ytemp);
	m_cam->ProcessCursorMovemment(xtemp, ytemp, true);
	m_lastCursorX = x;
	m_lastCursorY = y;
}