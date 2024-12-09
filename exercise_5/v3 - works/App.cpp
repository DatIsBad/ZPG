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

	

	



	m_scenes.push_back(new Scene());
	m_scenes.push_back(new Scene());
	m_scenes.push_back(new Scene());
	m_scenes.push_back(new Scene());
	m_scenes.push_back(new Scene());
	int activeScene = 0;
	float trans = 0.5f;
	float scale = 0.3;
	//--------------------------------------------------- SCENE1
	Scene* scene1 = m_scenes[0];
	m_control = new Controller(m_window, scene1, &activeScene);

	for (int i = 0; i < 50; i++) {
		scene1->addModel("tree", 0);
		scene1->addScaleObjModel( i, glm::vec3( (float)(std::rand() % 10) / 100.0 ));
		scene1->addRotationObjModel( i, glm::radians( (float)(std::rand() % 360) ), glm::vec3(0.0f, 1.0f, 0.0f));
		scene1->addTranslationObjModel( i, glm::vec3((float)(std::rand() % 2000 - 1000) / 100, 0.f, (float)(std::rand() % 2000 - 1000) / 100));
	}

	for (int i = 0; i < 50; i++) {
		scene1->addModel("bushes", 0);
		scene1->addScaleObjModel( i + 50, glm::vec3((float)(std::rand() % 10) / 100.0));
		scene1->addRotationObjModel( i + 50, glm::radians((float)(std::rand() % 360)), glm::vec3(0.0f, 1.0f, 0.0f));
		scene1->addTranslationObjModel( i + 50, glm::vec3((float)(std::rand() % 2000 - 1000) / 100, 0.f, (float)(std::rand() % 2000 - 1000) / 100));
	}

	scene1->addShader(0);
	scene1->addModel(plain, std::size(plain), 1);
	scene1->addScaleObjModel(100, glm::vec3(100.f));

	
	scene1->addShader(3);
	scene1->addModel("sphere", 2);
	scene1->addModel("sphere", 2);
	scene1->addModel("sphere", 2);
	scene1->addModel("sphere", 2);
	scene1->addScaleObjModel(101, glm::vec3(scale));
	scene1->addScaleObjModel(102, glm::vec3(scale));
	scene1->addScaleObjModel(103, glm::vec3(scale));
	scene1->addScaleObjModel(104, glm::vec3(scale));
	scene1->addTranslationObjModel(101, glm::vec3(trans, 0.0f, trans));
	scene1->addTranslationObjModel(102, glm::vec3(-trans, 0.0f, trans));
	scene1->addTranslationObjModel(103, glm::vec3(trans, 0.0f, -trans));
	scene1->addTranslationObjModel(104, glm::vec3(-trans, 0.0f, -trans));

	//--------------------------------------------------- SCENE2
	Scene* scene2 = m_scenes[1];
	

	scene2->addShader(0);
	scene2->addModel("sphere", 1);
	scene2->addModel("sphere", 1);
	scene2->addModel("sphere", 1);
	scene2->addModel("sphere", 1);
	scene2->addScaleObjModel(0, glm::vec3(scale));
	scene2->addScaleObjModel(1, glm::vec3(scale));
	scene2->addScaleObjModel(2, glm::vec3(scale));
	scene2->addScaleObjModel(3, glm::vec3(scale));
	scene2->addTranslationObjModel(0, glm::vec3(trans, 0.0f, trans));
	scene2->addTranslationObjModel(1, glm::vec3(-trans, 0.0f, trans));
	scene2->addTranslationObjModel(2, glm::vec3(trans, 0.0f, -trans));
	scene2->addTranslationObjModel(3, glm::vec3(-trans, 0.0f, -trans));

	//--------------------------------------------------- SCENE3
	Scene* scene3 = m_scenes[2];
	scene3->addShader(1);
	scene3->addModel("sphere", 1);
	scene3->addModel("sphere", 1);
	scene3->addModel("sphere", 1);
	scene3->addModel("sphere", 1);
	scene3->addScaleObjModel(0, glm::vec3(scale));
	scene3->addScaleObjModel(1, glm::vec3(scale));
	scene3->addScaleObjModel(2, glm::vec3(scale));
	scene3->addScaleObjModel(3, glm::vec3(scale));
	scene3->addTranslationObjModel(0, glm::vec3(trans, 0.0f, trans));
	scene3->addTranslationObjModel(1, glm::vec3(-trans, 0.0f, trans));
	scene3->addTranslationObjModel(2, glm::vec3(trans, 0.0f, -trans));
	scene3->addTranslationObjModel(3, glm::vec3(-trans, 0.0f, -trans));


	//--------------------------------------------------- SCENE4
	Scene* scene4 = m_scenes[3];
	scene4->addShader(2);
	scene4->addModel("sphere", 1);
	scene4->addModel("sphere", 1);
	scene4->addModel("sphere", 1);
	scene4->addModel("sphere", 1);
	scene4->addScaleObjModel(0, glm::vec3(scale));
	scene4->addScaleObjModel(1, glm::vec3(scale));
	scene4->addScaleObjModel(2, glm::vec3(scale));
	scene4->addScaleObjModel(3, glm::vec3(scale));
	scene4->addTranslationObjModel(0, glm::vec3(trans, 0.0f, trans));
	scene4->addTranslationObjModel(1, glm::vec3(-trans, 0.0f, trans));
	scene4->addTranslationObjModel(2, glm::vec3(trans, 0.0f, -trans));
	scene4->addTranslationObjModel(3, glm::vec3(-trans, 0.0f, -trans));

	//--------------------------------------------------- SCENE5
	Scene* scene5 = m_scenes[4];
	scene5->addShader(3);
	scene5->addModel("sphere", 1);
	scene5->addModel("sphere", 1);
	scene5->addModel("sphere", 1);
	scene5->addModel("sphere", 1);
	scene5->addScaleObjModel(0, glm::vec3(scale));
	scene5->addScaleObjModel(1, glm::vec3(scale));
	scene5->addScaleObjModel(2, glm::vec3(scale));
	scene5->addScaleObjModel(3, glm::vec3(scale));
	scene5->addTranslationObjModel(0, glm::vec3(trans, 0.0f, trans));
	scene5->addTranslationObjModel(1, glm::vec3(-trans, 0.0f, trans));
	scene5->addTranslationObjModel(2, glm::vec3(trans, 0.0f, -trans));
	scene5->addTranslationObjModel(3, glm::vec3(-trans, 0.0f, -trans));




	glEnable(GL_DEPTH_TEST);
	//--------------------
	while (!glfwWindowShouldClose(m_window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < m_scenes.size(); i++) {
			if (activeScene == i) {
				m_control->change_observer(m_scenes.at(i));
				m_scenes.at(i)->runScene();
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


