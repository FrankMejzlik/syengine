#include "Camera.h"
#include "CommonValues.h"

using namespace WeSp;

namespace WeSp 
{

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed):
  position(startPosition), 
  worldUp(startUp), 
  yaw(startYaw), 
  pitch(startPitch), 
  front(glm::vec3(0.0f, 0.0f, -1.0f)), 
  moveSpeed(startMoveSpeed), 
  turnSpeed(startTurnSpeed),
  torchEnabled(false)
{
	Update();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat speed = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * speed;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * speed;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * speed;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * speed;
	}
}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::GetCameraPosition()
{
  return position;
}

glm::vec3 Camera::GetCameraDirection()
{
  return glm::normalize(front);
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}

}