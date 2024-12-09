#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Observer.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera 
{
public:
	Camera();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(char direction, float deltaTime);
	void ProcessCursorMovemment(float xoffset, float yoffset, bool constrainPitch);

private:
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

	void updateCameraVectors();
};

