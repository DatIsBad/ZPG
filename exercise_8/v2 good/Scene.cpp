#include "Scene.h"

Scene::Scene(const Controller& controller): m_controller(controller) {
	//m_model = new Model("sphere");
	std::srand(std::time(nullptr));	//current time is seed
	m_cam = new Camera();
	m_TextureMan = new TextureManager();

	m_lastCursorX = 0;
	m_lastCursorY = 0;
	height_window = 1200;
	width_window = 1200;
	cameraLocked = true;
	cameraFlashlight = true;

	const_cast<Controller&>(m_controller).addObserver(this);
	m_active = false;
}

Scene::~Scene() {
	for (ShaderProgram* shader : m_shaders) {
		delete shader;  // Manually delete each allocated Shader object
	}

	for (DrawableObject* dobj : m_DObj) {
		delete dobj;  // Manually delete each allocated DrawableObject object
	}

	for (LightGroup* lig : m_light) {
		delete lig;  // Manually delete each allocated DrawableObject object
	}

	const_cast<Controller&>(m_controller).removeObserver(this);

	delete m_cam;
	delete m_TextureMan;
}

int Scene::runScene() {
	//get deltaTime
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;

	//draw all models
	for (size_t i = 0; i < m_shaders.size(); i++) {
		ShaderProgram* shader = m_shaders[i];
		LightGroup* light = m_light[i];
		DrawableObject* DObj = m_DObj[i];

		shader->useShaderProgram();
		light->updateAll(shader);
		DObj->drawModels(shader, m_TextureMan);
	}

	//check for shader errors
	for (ShaderProgram* shader : m_shaders) {
		// Access each Shader* in the vector
		if (shader->checkShaderProgram() == -1)
		{
			return -1;
		}
	}

	return 1;
}


//-----------------------------------------------------------
void Scene::addDOShader() {
	m_DObj.push_back(new DrawableObject());
	m_shaders.push_back(new ShaderProgram(*m_cam));

	m_light.push_back(new LightGroup());
	//m_light[m_light.size() - 1]->addLight(0, false, glm::vec3(0, 0, 0));
}

void Scene::addDOShader(int type) {
	m_DObj.push_back(new DrawableObject());
	m_shaders.push_back(new ShaderProgram(type, *m_cam));
	
	m_light.push_back(new LightGroup());
	//m_light[m_light.size() - 1]->addLight(0, false, glm::vec3(0, 0, 0));
}

void Scene::addDOShader(const char* vertex_shader, const char* fragment_shader) {
	m_DObj.push_back(new DrawableObject());
	m_shaders.push_back(new ShaderProgram(vertex_shader, fragment_shader, *m_cam));
	
	m_light.push_back(new LightGroup());
	//m_light[m_light.size() - 1]->addLight(0, false, glm::vec3(0, 0, 0));
}



//-----------------------------------------------------------
void Scene::addLight(int idDOShader, int type, bool isCamera, glm::vec3 lightPos, bool randomMovement) {
	m_light[idDOShader]->addLight(type, isCamera, lightPos);
	if(randomMovement == true)
		m_light[idDOShader]->randMovement(m_light[idDOShader]->getSize() - 1);
}

void Scene::addLight(int idDOShader, int type, bool isCamera, glm::vec3 lightPos, glm::vec3 color, bool randomMovement) {
	m_light[idDOShader]->addLight(type, isCamera, lightPos, color);
	if (randomMovement == true)
		m_light[idDOShader]->randMovement(m_light[idDOShader]->getSize() - 1);
}

void Scene::addLight(int idDOShader, int type, bool isCamera, glm::vec3 lightPos, glm::vec3 color, float intensity, float ambientStrength, float specularStrength, bool randomMovement) {
	m_light[idDOShader]->addLight(type, isCamera, lightPos, color, intensity, ambientStrength, specularStrength);
	if (randomMovement == true)
		m_light[idDOShader]->randMovement(m_light[idDOShader]->getSize() - 1);
}


//-----------------------------------------------------------
void Scene::addModel(int idDOShader, const char model[]) { //choose model
	m_DObj.at(idDOShader)->addModel(model);
}

void Scene::addModel(int idDOShader, const float model[], int size) { //choose model
	m_DObj.at(idDOShader)->addModel(model, size);
}

int Scene::getSizeDO(int idDOShader) {
	return m_DObj[idDOShader]->getmodelCount();
}

//-----------------------------------------------------------
void Scene::addRotationObjModel(int idDOShader, int moID, float angle, glm::vec3 rotation) {
	m_DObj.at(idDOShader)->addRotationModel(moID, angle, rotation);
}

void Scene::Scene::addScaleObjModel(int idDOShader, int moID, glm::vec3 scaleValue) {
	m_DObj.at(idDOShader)->addScaleModel(moID, scaleValue);
}


void Scene::addTranslationObjModel(int idDOShader, int moID, glm::vec3 translation) {
	m_DObj.at(idDOShader)->addTranslationModel(moID, translation);
}



//-----------------------------------------------------------
void Scene::updateObservedKey(char userInput) {
	m_cam->ProcessKeyboard(userInput, m_deltaTime);
}

void Scene::updateObservedCursor(double x, double y, bool locked) {
	float xtemp = x - m_lastCursorX;
	float ytemp = m_lastCursorY - y;
	m_lastCursorX = x;
	m_lastCursorY = y;

	if(locked == true)
		m_cam->ProcessCursorMovemment(xtemp, ytemp, true);
}

void Scene::makeLightMove(int id_lightgroup, int id_light) {
	m_light[id_lightgroup]->randMovement(id_light);
}

int Scene::getSizeLight(int idDOShader) {
	return m_light[idDOShader]->getSize();
}

void Scene::setLightAttenuation(int idDOShader, int lightID, float constant, float linear, float quadratic, float range) {
	m_light[idDOShader]->setAttenuation(lightID, constant, linear, quadratic, range);
}



void Scene::prepareTextureManager() {
	m_TextureMan->loadCubeMap("morningSky", 0);
	m_TextureMan->loadCubeMap("nightSky", 1);
	m_TextureMan->loadTexture("test", "textures/test.png");
	m_TextureMan->loadTexture("grass", "textures/grass.jpg");

	printf("TEXTURES LOADED\n");
}

void Scene::prepareNightSky() {
	addDOShader(4);
	addModel( m_shaders.size() - 1, "box_in");
	addScaleObjModel(m_shaders.size() - 1, 0, glm::vec3(600.0f));
	m_DObj.at(m_shaders.size() - 1)->assignTexture(0, "nightSky", 1);

	printf("CUBEMAP LOADED\n");
}

void Scene::assignTexture(int idDOShader, int moID, std::string textureName, int textureMultiplier) {
	m_DObj[idDOShader]->assignTexture(moID, textureName, textureMultiplier);
}
















void Scene::update() {
	if (m_active == true) {
		if (m_controller.getXCursor() != m_lastCursorX || m_controller.getYCursor() != m_lastCursorY) {
			updateObservedCursor(m_controller.getXCursor(), m_controller.getYCursor(), m_controller.getLocked());
		}
		if (m_controller.getHeightWindow() != height_window || m_controller.getWidthWindow() != width_window) {
			m_cam->updateSizes(m_controller.getHeightWindow(), m_controller.getWidthWindow());
			height_window = m_controller.getHeightWindow();
			width_window = m_controller.getWidthWindow();
			printf("window resize %d %d\n", width_window, height_window);
		}
		if (m_controller.getLastPressed() != ' ') {
			updateObservedKey(m_controller.getLastPressed());
		}
		if (cameraFlashlight != m_controller.getFlashlight()) {
			cameraFlashlight = m_controller.getFlashlight();

			if (cameraFlashlight == false) {
				for (int i = 0; i < m_light.size(); i++) {
					m_light[i]->disableCameraLight();
				}
			}
			else {
				for (int i = 0; i < m_light.size(); i++) {
					m_light[i]->enableCameraLight();
				}
			}


		}
	}
}