#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Observer.h"


class Controller
{
public:
	Controller(GLFWwindow* window, int* scene);
	~Controller();

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	const int& getWidthWindow() const;
	const int& getHeightWindow() const;
	const double& getXCursor() const;
	const double& getYCursor() const;
	const char& getLastPressed() const;
	const bool& getLocked() const;
	const bool& getFlashlight() const;


	void useKeys(int key, int scancode, int action, int mods);
	void useCursorPos( double x, double y);
	void useResize(int width, int height);


	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void error_callback(int error, const char* description);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

private:
	std::vector<Observer*> observers;
	GLFWwindow* m_window;
	bool locked;
	bool flashlight;

	int* m_scene;

	int height_window;
	int width_window;

	double x_cursor;
	double y_cursor;
	char last_pressed;

};

