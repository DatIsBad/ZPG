#include "Controller.h"
Controller::Controller(GLFWwindow* window, Observer* obj) {
	m_obj = obj;
	m_window = window;
	locked = true;

	//grab cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

Controller::~Controller() {
	delete m_obj;
	delete m_window;
}

void Controller::change_observer(Observer* obj) {
	m_obj = obj;
}

void Controller::error_callback(int error, const char* description){
	fputs(description, stderr);
}


void Controller::useKeys(int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W ) {
		m_obj->updateObservedKey('W');
	}
	if (key == GLFW_KEY_A ) {
		m_obj->updateObservedKey('A');
	}
	if (key == GLFW_KEY_S ) {
		m_obj->updateObservedKey('S');
	}
	if (key == GLFW_KEY_D ) {
		m_obj->updateObservedKey('D');
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		if (locked == true) {
			//grab cursor
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			locked = false;
		}
		else  {
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			locked = true;
		}
	}
	
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::useCursorPos(double x, double y) {


	m_obj->updateObservedCursor(x, y);
	//printf("cursor %f %f\n", x,y);
}





//-----------------------------------------------------------------------------------------------------------

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	



	Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));

	// Forward the call to the non-static keyCallback method
	if (controller) {
		controller->useKeys(key, scancode, action, mods);
	}
}

void Controller::window_focus_callback(GLFWwindow* window, int focused){ 
	printf("window_focus_callback \n"); 
}

void Controller::window_iconify_callback(GLFWwindow* window, int iconified){
	printf("window_iconify_callback \n"); 
}

void Controller::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
	glfwGetFramebufferSize(window, &width, &height);
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y) {
	Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));

	// Forward the call to the non-static keyCallback method
	if (controller) {
		controller->useCursorPos(x,y);
	} 
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}