#include "Camera.h"
#include "CommonValues.h"
#include <iostream>
using namespace SYE;

namespace SYE 
{

Camera::Camera(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
  GLfloat startMoveSpeed, GLfloat startTurnSpeed
) :
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
  _moveSpeed(startMoveSpeed),
  _firstPersonTurnSpeed(startTurnSpeed),
  _eCameraMode(eCameraModes::FIRST_PERSON_MODE),
  _bIsDragingOn(false),
  _editorModeTurnSpeed(3.0f)
{
	UpdateFirstPersonMode();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat speed = _moveSpeed * deltaTime;

  if (keys[GLFW_KEY_K])
  {
    _eCameraMode = eCameraModes::EDITOR_MODE;
  }

  if (keys[GLFW_KEY_L])
  {
    _eCameraMode = eCameraModes::FIRST_PERSON_MODE;
  }


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

void Camera::MouseKeyControl(bool* keys, GLfloat deltaTime)
{

  if (keys[GLFW_MOUSE_BUTTON_RIGHT])
  {
    _bIsDragingOn = true;
  }
  else
  {
    _bIsDragingOn = false;
  }

  DLog(eLogType::Info, "%d, %d",keys[GLFW_MOUSE_BUTTON_RIGHT],_bIsDragingOn)

}


void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
    _mouseXChange = xChange;
    _mouseYChange = yChange;
 
    dfloat firstPersonChangeX = xChange * _firstPersonTurnSpeed;
    dfloat firstPersonChangeY = yChange * _firstPersonTurnSpeed;

    dfloat editorModeChangeX = xChange * _editorModeTurnSpeed;
    dfloat editorModeChangeY = yChange * _editorModeTurnSpeed;

    yaw += firstPersonChangeX;
    pitch += firstPersonChangeY;

    _inverseYaw -= editorModeChangeX;
    _inversePitch -= editorModeChangeY;

    if (_inversePitch > 89.0f)
    {
      _inversePitch = -89.0f;
    }

    if (_inversePitch < -89.0f)
    {
      _inversePitch = 89.0f;
    }

    if (pitch > 89.0f)
    {
      pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
      pitch = -89.0f;
    }

    DLog(eLogType::Info, "0---%d, %d", _eCameraMode, _bIsDragingOn);
    if (_bIsDragingOn && _eCameraMode == eCameraModes::EDITOR_MODE)
    {
      UpdateEditorMode();
    }
    else if ( _eCameraMode == eCameraModes::FIRST_PERSON_MODE)
    {
      UpdateFirstPersonMode();
    }
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

void Camera::UpdateEditorMode()
{
  front.x += cos(glm::radians(_inverseYaw)) * cos(glm::radians(_inversePitch));
  front.y = sin(glm::radians(_inversePitch));
  front.z = sin(glm::radians(_inverseYaw)) * cos(glm::radians(_inversePitch));
  front = glm::normalize(front);

  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}

void Camera::UpdateFirstPersonMode()
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