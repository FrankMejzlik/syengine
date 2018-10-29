#include "Camera.h"
#include "CommonValues.h"
#include <iostream>
using namespace WeSp;

namespace WeSp 
{

Camera::Camera(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed
):
  WorldEntity(
    pComponentManager,
    startPosition,
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
  ),
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

  if (keys[GLFW_KEY_SPACE] && !keys[GLFW_KEY_LEFT_SHIFT])
  {
    position += up * speed;
  }

  if (keys[GLFW_KEY_SPACE] && keys[GLFW_KEY_LEFT_SHIFT])
  {
    position -= up * speed;
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