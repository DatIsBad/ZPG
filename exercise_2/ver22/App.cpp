#include "App.h"

App::App() {
	printf("App created\n");
}


App::~App() {
	printf("App deleted\n");
	delete m_buffer;
	delete m_shader1;
	delete m_shader2;
	delete m_shader3;

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

	m_buffer = new Buffer();
	
	float points1[] = {
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	-0.25f, 0.75f, 0.0f,
	0.75f, 0.75f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.75f, 0.75f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.75f, 0.75f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.75f, 0.75f, 0.0f
	};

	float points2[] = {
	-0.5f, 0.5f, 0.0f,
	-0.25f, 0.75f, 0.0f,
	0.75f, 0.75f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.75f, 0.75f, 0.0f
	};

	float points3[] = {
	0.5f, -0.5f, 0.0f,
	0.75f, -0.25f, 0.0f,
	0.75f, 0.75f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.75f, 0.75f, 0.0f
	};
	
	m_buffer->addPoint(points1, std::size(points1));
	m_shader1 = new Shader(glm::vec3(1, 0.5, 0));
	m_shader2 = new Shader(glm::vec3(0, 0.5, 0));
	m_shader3 = new Shader(glm::vec3(1, 0.5, 1));
	
	//--------------------
	while (!glfwWindowShouldClose(m_window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//run shader + bind buffer
		
		m_shader1->useShaderProgram();
		m_buffer->bindVAO();

		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 6); //mode,first,count

		m_shader2->useShaderProgram();
		//m_buffer1->bindVAO();

		// draw triangles
		glDrawArrays(GL_TRIANGLES, 6, 6); //mode,first,count

		m_shader3->useShaderProgram();
		//m_buffer1->bindVAO();

		// draw triangles
		glDrawArrays(GL_TRIANGLES, 12, 6); //mode,first,count



		if (m_shader1->checkShaderProgram() == -1 || m_shader2->checkShaderProgram() == -1 || m_shader3->checkShaderProgram() == -1)
		{
			break;
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
