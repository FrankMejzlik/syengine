#include "Camera_.h"

#include <iostream>

#include "Window.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;

namespace SYE 
{

Camera::Camera(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
) noexcept:
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true,
    CAMERA
  ),
  
  _mode(eCameraModes::NORMAL),
  _isDragingOn(false)
#if !INPUT_MANAGER_REFACTORED
  ,_worldUp(Vector3f(0.0f, 1.0f, 0.0f)),
  _yaw(0.0f),
  _pitch(0.0f),
  _frontDirection(Vector3f(0.0f, 0.0f, -1.0f)),
  _moveSpeed(5.0f),
  _firstPersonTurnSpeed(1.0),
  _editorModeTurnSpeed(0.05f),
  _inverseYaw(0.0f),
  _inversePitch(0.0f)
#endif
{
  _type = eType::CAMERA;

#if !INPUT_MANAGER_REFACTORED
  // Calculate correct values right away
  Update();
#endif
}

void Camera::Refresh()
{
  /**
   * Update all quick refs to sibling Components
   */

  // Update Transform quick ref
  if (!_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].empty())
  {
    _pTransform = static_cast<Transform*>(_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].begin()->second);
  }
  
}

glm::mat4 Camera::CalculateViewMatrix()
{
  Vector3f position = GetCameraPosition();

	return glm::lookAt(position.GetData(), (position + _pTransform->GetZDir()).GetData(), _pTransform->GetYDir().GetData());
}


Vector3f Camera::GetCameraPosition() const
{
  return _pTransform->GetPosition();
}

Vector3f Camera::GetCameraDirection() const
{
  return Normalize(_pTransform->GetZDir());
}

#if !INPUT_MANAGER_REFACTORED

void Camera::Update()
{
  if (_mode == eCameraModes::NORMAL)
  {
    UpdateFirstPersonMode();
  }
  else
  {
    UpdateEditorMode();
  }
}

void Camera::UpdateEditorMode()
{
  _frontDirection.SetX(cos(ToRadians(_inverseYaw)) * cos(ToRadians(_inversePitch)));
  _frontDirection.SetY(sin(ToRadians(_inversePitch)));
  _frontDirection.SetZ(sin(ToRadians(_inverseYaw)) * cos(ToRadians(_inversePitch)));
  _frontDirection = Normalize(_frontDirection);


  _right = Normalize(Cross(_frontDirection, _worldUp));
  _up = Normalize(Cross(_right, _frontDirection));
}

void Camera::UpdateFirstPersonMode()
{
	_frontDirection.SetX(cos(ToRadians(_yaw)) * cos(ToRadians(_pitch)));
	_frontDirection.SetY(sin(ToRadians(_pitch)));
	_frontDirection.SetZ(sin(ToRadians(_yaw)) * cos(ToRadians(_pitch)));
	_frontDirection = Normalize(_frontDirection);

	_right = Normalize(Cross(_frontDirection, _worldUp));
  _up = Normalize(Cross(_right, _frontDirection));
}

void Camera::KeyControl(Window* pMainWindow, dfloat deltaTime)
{
  Vector3f position = GetCameraPosition();

  bool* keys = pMainWindow->GetKeys();

  dfloat deltaSpeed = _moveSpeed * deltaTime;

  if (keys[GLFW_KEY_K])
  {
    _mode = eCameraModes::EDITOR_CAMERA;
    pMainWindow->ShowCursor();
  }

  if (keys[GLFW_KEY_L])
  {
    _mode = eCameraModes::NORMAL;
    pMainWindow->HideCursor();
  }


  if (keys[GLFW_KEY_W])
  {
    position = position + _frontDirection * deltaSpeed;
  }

  if (keys[GLFW_KEY_S])
  {
    position = position - (_frontDirection * deltaSpeed);
  }

  if (keys[GLFW_KEY_A])
  {
    position = position - (_right * deltaSpeed);
  }

  if (keys[GLFW_KEY_D])
  {
    position = position + _right * deltaSpeed;
  }

  if (keys[GLFW_KEY_SPACE] && !keys[GLFW_KEY_LEFT_SHIFT])
  {
    position = position + (_up * deltaSpeed);
  }

  if (keys[GLFW_KEY_SPACE] && keys[GLFW_KEY_LEFT_SHIFT])
  {
    position = position - (_up * deltaSpeed);
  }

  // Update position in Transform Component
  _pTransform->SetPosition(position);
}

void Camera::MouseKeyControl(bool* keys, dfloat deltaTime)
{
  UNREFERENCED_PARAMETER(deltaTime);

  if (keys[GLFW_MOUSE_BUTTON_RIGHT])
  {
    _isDragingOn = true;
  }
  else
  {
    _isDragingOn = false;
  }
}

void Camera::MouseControl(dfloat xChange, dfloat yChange)
{
  _mouseXChange = xChange;
  _mouseYChange = yChange;

  dfloat firstPersonChangeX = xChange * _firstPersonTurnSpeed;
  dfloat firstPersonChangeY = yChange * _firstPersonTurnSpeed;

  dfloat editorModeChangeX = xChange * _editorModeTurnSpeed;
  dfloat editorModeChangeY = yChange * _editorModeTurnSpeed;

  _yaw += firstPersonChangeX;
  _pitch += firstPersonChangeY;

  if (_pitch > 89.0f)
  {
    _pitch = 89.0f;
  }

  if (_pitch < -89.0f)
  {
    _pitch = -89.0f;
  }

  if (_isDragingOn && _mode == eCameraModes::EDITOR_CAMERA)
  {
    _inverseYaw -= editorModeChangeX;
    _inversePitch -= editorModeChangeY;

    if (_inversePitch > 89.0f)
    {
      _inversePitch = 89.0f;
    }

    if (_inversePitch < -89.0f)
    {
      _inversePitch = -89.0f;
    }

    UpdateEditorMode();
  }
  else
  {
    UpdateFirstPersonMode();
  }
}


#endif

}