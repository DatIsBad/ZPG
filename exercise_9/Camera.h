#pragma once
//********************************************
// PHA0051
// 08/12/2024
//********************************************

#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Observer.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 50.f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera 
{
public:
	Camera();
	~Camera();
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;
	const glm::vec3& GetCameraPos() const;
	const glm::vec3& getCameraDir() const;


	void ProcessKeyboard(char direction, float deltaTime);
	void ProcessCursorMovemment(float xoffset, float yoffset, bool constrainPitch);
	void updateSizes(int height, int width);
	void updateShaders();
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	
private:
	// sizes
	float height;
	float width;

	// Camera attributes
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;	
	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraWorldUp;

	// Camera options
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_fov;

	// euler Angles
	float m_yaw;
	float m_pitch;

	// Observer on ShaderProgram
	std::vector<Observer*> observers;

	//
	int whichLight;


	void updateCameraVectors();
};

