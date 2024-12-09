#include "App.h"

App::App() {
	printf("App created\n");

}


App::~App() {
	printf("App deleted\n");
	for (Scene* scene : m_scenes) {
		delete scene;  // Manually delete each allocated Model object
	}

}


void App::RunApp() {
	printf("App running\n");
	
	glfwSetErrorCallback(Controller::error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	m_window = glfwCreateWindow(1200, 1200, "ZPG", NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("Khai Dat Phan - PHA0051\n");
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	

	int activeScene = 0;
	float trans = 0.5f;
	float scale = 0.3;
	m_control = new Controller(m_window, &activeScene);

	printf("PUSH SCENE\n");
	m_scenes.push_back(new Scene(*m_control));
	m_scenes.push_back(new Scene(*m_control));
	m_scenes.push_back(new Scene(*m_control));
	m_scenes.push_back(new Scene(*m_control));
	m_scenes.push_back(new Scene(*m_control));

	//--------------------------------------------------- SCENE1
	Scene* scene1 = m_scenes[0];
	

	
	scene1->addDOShader(2);
	scene1->addLight(0, glm::vec3(3.0, 3.0, 10.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);
	scene1->addLight(0, glm::vec3(3.0, 3.0, 3.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);
	scene1->addLight(0, glm::vec3(2.0, 3.0, -2.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);
	scene1->addLight(0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);
	scene1->addLight(0, glm::vec3(3.0, 3.0, 10.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);
	scene1->addLight(0, glm::vec3(3.0, 3.0, 3.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);
	scene1->addLight(0, glm::vec3(2.0, 3.0, -2.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);
	scene1->addLight(0, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.5), 0.5, 0.01f, 0.05f, true);


	for (int i = 0; i < 50; i++) {
		scene1->addModel(0, "tree");
		scene1->addScaleObjModel(0, (scene1->getSizeDO(0) - 1), glm::vec3((float)((std::rand() % 30) + 30) / 200.0));
		scene1->addRotationObjModel(0, (scene1->getSizeDO(0) - 1), glm::radians( (float)(std::rand() % 360) ), glm::vec3(0.0f, 1.0f, 0.0f));
		scene1->addTranslationObjModel(0, (scene1->getSizeDO(0) - 1), glm::vec3((float)(std::rand() % 2000 - 1000) / 100, 0.f, (float)(std::rand() % 2000 - 1000) / 100));
		
	}

	for (int i = 0; i < 50; i++) {
		scene1->addModel(0, "bushes");
		scene1->addScaleObjModel(0, (scene1->getSizeDO(0) - 1), glm::vec3((float)((std::rand() % 30) + 30) / 200.0));
		scene1->addRotationObjModel( 0, (scene1->getSizeDO(0) - 1), glm::radians((float)(std::rand() % 360)), glm::vec3(0.0f, 1.0f, 0.0f));
		scene1->addTranslationObjModel( 0, (scene1->getSizeDO(0) - 1), glm::vec3((float)(std::rand() % 2000 - 1000) / 100, 0.f, (float)(std::rand() % 2000 - 1000) / 100));
	}

	scene1->addModel(0, plain, std::size(plain));
	scene1->addScaleObjModel(0, 100, glm::vec3(100.f));

	
	//scene1->addDOShader(3);
	
	for (int i = 0; i < 50; i++) {
		scene1->addModel(0, "sphere");
		scene1->addScaleObjModel(0, scene1->getSizeDO(0) - 1, glm::vec3(scale));
		scene1->addTranslationObjModel(0, scene1->getSizeDO(0) - 1, glm::vec3(i + 2, 0.0f, 0.0f));
	}



	//--------------------------------------------------- SCENE2
	Scene* scene2 = m_scenes[1];
	
	printf("SCENE2 ADD DOS\n");
	scene2->addDOShader(0);
	scene2->addModel(0, "sphere");
	scene2->addModel(0, "sphere");
	scene2->addModel(0, "sphere");
	scene2->addModel(0, "sphere");
	scene2->addScaleObjModel(0, 0, glm::vec3(scale));
	scene2->addScaleObjModel(0, 1, glm::vec3(scale));
	scene2->addScaleObjModel(0, 2, glm::vec3(scale));
	scene2->addScaleObjModel(0, 3, glm::vec3(scale));
	scene2->addTranslationObjModel(0, 0, glm::vec3(trans, 0.0f, trans));
	scene2->addTranslationObjModel(0, 1, glm::vec3(-trans, 0.0f, trans));
	scene2->addTranslationObjModel(0, 2, glm::vec3(trans, 0.0f, -trans));
	scene2->addTranslationObjModel(0, 3, glm::vec3(-trans, 0.0f, -trans));

	//--------------------------------------------------- SCENE3
	Scene* scene3 = m_scenes[2];
	scene3->addDOShader(1);
	scene3->addModel(0, "sphere");
	scene3->addModel(0, "sphere");
	scene3->addModel(0, "sphere");
	scene3->addModel(0, "sphere");
	scene3->addScaleObjModel(0, 0, glm::vec3(scale));
	scene3->addScaleObjModel(0, 1, glm::vec3(scale));
	scene3->addScaleObjModel(0, 2, glm::vec3(scale));
	scene3->addScaleObjModel(0, 3, glm::vec3(scale));
	scene3->addTranslationObjModel(0, 0, glm::vec3(trans, 0.0f, trans));
	scene3->addTranslationObjModel(0, 1, glm::vec3(-trans, 0.0f, trans));
	scene3->addTranslationObjModel(0, 2, glm::vec3(trans, 0.0f, -trans));
	scene3->addTranslationObjModel(0, 3, glm::vec3(-trans, 0.0f, -trans));


	//--------------------------------------------------- SCENE4
	Scene* scene4 = m_scenes[3];
	scene4->addDOShader(2);
	scene4->addModel(0, "sphere");
	scene4->addModel(0, "sphere");
	scene4->addModel(0, "sphere");
	scene4->addModel(0, "sphere");
	scene4->addScaleObjModel(0, 0, glm::vec3(scale));
	scene4->addScaleObjModel(0, 1, glm::vec3(scale));
	scene4->addScaleObjModel(0, 2, glm::vec3(scale));
	scene4->addScaleObjModel(0, 3, glm::vec3(scale));
	scene4->addTranslationObjModel(0, 0, glm::vec3(trans, 0.0f, trans));
	scene4->addTranslationObjModel(0, 1, glm::vec3(-trans, 0.0f, trans));
	scene4->addTranslationObjModel(0, 2, glm::vec3(trans, 0.0f, -trans));
	scene4->addTranslationObjModel(0, 3, glm::vec3(-trans, 0.0f, -trans));

	//--------------------------------------------------- SCENE5
	Scene* scene5 = m_scenes[4];
	scene5->addDOShader(3);
	scene5->addModel(0, "sphere");
	scene5->addModel(0, "sphere");
	scene5->addModel(0, "sphere");
	scene5->addModel(0, "sphere");
	scene5->addScaleObjModel(0, 0, glm::vec3(scale));
	scene5->addScaleObjModel(0, 1, glm::vec3(scale));
	scene5->addScaleObjModel(0, 2, glm::vec3(scale));
	scene5->addScaleObjModel(0, 3, glm::vec3(scale));
	scene5->addTranslationObjModel(0, 0, glm::vec3(trans, 0.0f, trans));
	scene5->addTranslationObjModel(0, 1, glm::vec3(-trans, 0.0f, trans));
	scene5->addTranslationObjModel(0, 2, glm::vec3(trans, 0.0f, -trans));
	scene5->addTranslationObjModel(0, 3, glm::vec3(-trans, 0.0f, -trans));




	glEnable(GL_DEPTH_TEST);
	//--------------------
	while (!glfwWindowShouldClose(m_window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < m_scenes.size(); i++) {
			if (activeScene == i) {
				m_scenes.at(i)->runScene();
				m_scenes.at(i)->m_active = true;
			}
			else {
				m_scenes.at(i)->m_active = false;
			}
		}

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(m_window);
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}


