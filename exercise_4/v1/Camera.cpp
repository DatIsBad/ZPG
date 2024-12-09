#include "Camera.h"

Camera::Camera() {
	//set camera position
	m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	//set direction of camera
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_cameraDirection = glm::normalize(m_cameraPos - cameraTarget);

	//set right axis of camera
	m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_cameraWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_cameraRight = glm::normalize(glm::cross(m_cameraUp, m_cameraDirection));

	//atributes
	m_movementSpeed = 2.5f;
	m_mouseSensitivity = SENSITIVITY;
	m_fov = ZOOM;
	m_yaw = YAW;
	m_pitch = PITCH;
}


//----------------------------------------------------
glm::mat4 Camera::GetViewMatrix()
{	
	return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

// Process keyboard input
void Camera::ProcessKeyboard(char direction, float deltaTime) {
	float velocity = m_movementSpeed * deltaTime;

	printf("deltatime %f\n", m_movementSpeed);

	if (direction == 'W')
		m_cameraPos += m_cameraFront * velocity;
	if (direction == 'S')
		m_cameraPos -= m_cameraFront * velocity;
	if (direction == 'A')
		m_cameraPos -= m_cameraRight * velocity;
	if (direction == 'D')
		m_cameraPos += m_cameraRight * velocity;
}


void Camera::ProcessCursorMovemment(float xoffset, float yoffset, bool constrainPitch = true) {
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}













// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(front);
	// also re-calculate the Right and Up vector
	m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_cameraWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
}