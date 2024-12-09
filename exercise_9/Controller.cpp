#include "Controller.h"
Controller::Controller(GLFWwindow* window, int* scene) {
	m_window = window;
	locked = true;
	flashlight = false;
	
	m_scene = scene;

	x_cursor = 0;
	y_cursor = 0;
	last_pressed = ' ';

	height_window = 1200;
	width_window = 1200;

	//grab cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

Controller::~Controller() {
	// Clear the list of observers
	observers.clear();

	delete m_window;
}

//---------------------------------------------------------------------------------------
void Controller::addObserver(Observer* observer) {
	observers.push_back(observer);
}

void Controller::removeObserver(Observer* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

const int& Controller::getWidthWindow() const {
	return width_window;
}
const int& Controller::getHeightWindow() const {
	return height_window;
}
const double& Controller::getXCursor() const {
	return x_cursor;
}
const double& Controller::getYCursor() const {
	return y_cursor;
}
const char& Controller::getLastPressed() const {
	return last_pressed;
}

const bool& Controller::getLocked() const {
	return locked;
}

const bool& Controller::getFlashlight() const {
	return flashlight;
}










void Controller::error_callback(int error, const char* description){
	fputs(description, stderr);
}


void Controller::useKeys(int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W ) {
		last_pressed = 'W';
	}
	if (key == GLFW_KEY_A ) {
		last_pressed = 'A';
	}
	if (key == GLFW_KEY_S ) {
		last_pressed = 'S';
	}
	if (key == GLFW_KEY_D ) {
		last_pressed = 'D';
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

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		if (flashlight == true) {
			//grab cursor
			flashlight = false;
		}
		else {
			flashlight = true;
		}
	}





	
	//printf("KEY %d\n", key);
	//run scene
	if (key >= 49 && key <= 55) {
		*m_scene = key - 49;
	}

	for (int i = 0; i < observers.size(); i++) {
		observers.at(i)->update();
	}
	last_pressed = ' ';

	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::useCursorPos(double x, double y) {
	x_cursor = x;
	y_cursor = y;
	
	for (int i = 0; i < observers.size(); i++) {
		observers.at(i)->update();
	}
}

void Controller::useResize(int width, int height) {
	height_window = height;
	width_window = width;

	for (int i = 0; i < observers.size(); i++) {
		observers.at(i)->update();
	}
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

	Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));

	// Forward the call to the non-static keyCallback method
	if (controller) {
		controller->useResize(width, height);
	}
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