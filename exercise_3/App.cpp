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

	m_window = glfwCreateWindow(800, 800, "ZPG", NULL, NULL);
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

	Scene* scene1 = m_scenes[0];
	//scene1->addDObjShader();
	scene1->addModel(0, 3);
	scene1->addScaleObjModel(0, 0, glm::vec3(0.1f));
	scene1->addRotationObjModel(0, 0, glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));

	scene1->addModel(0, 3);
	scene1->addScaleObjModel(0, 1, glm::vec3(0.1f));
	scene1->addTranslationObjModel(0, 1, glm::vec3(0.5,0,0));

	scene1->addModel(0, 3);
	scene1->addScaleObjModel(0, 2, glm::vec3(0.05f));
	scene1->addTranslationObjModel(0, 2, glm::vec3(-0.5, 0, 0));

	scene1->addDObjShaderOneColor();
	scene1->addModel(1, 3);
	scene1->addScaleObjModel(1, 0, glm::vec3(0.2f));
	scene1->addTranslationObjModel(1, 0, glm::vec3(-0.8, 0, 0));

	Scene* scene2 = m_scenes[1];
	//scene2->addDObjShader();
	scene2->addModel(0, 0);
	scene2->addScaleObjModel(0, 0, glm::vec3(0.5f));

	int oneortwo = 1;
	glEnable(GL_DEPTH_TEST);
	//--------------------
	while (!glfwWindowShouldClose(m_window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//run scene
		if (glfwGetKey(m_window, 49) == GLFW_PRESS)
			oneortwo = 1;
		else if (glfwGetKey(m_window, 50) == GLFW_PRESS)
			oneortwo = 2;

		//run scene
		if (oneortwo == 1)
			scene1->runScene();
		else if (oneortwo == 2)
			scene2->runScene();



		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(m_window);
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}
