#include "Camera.h"

#include <iostream>

#include "Window.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;

Camera::Camera(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(
    pOwnerEntity, pOwnerComponent,
    true, true,
    slotIndex, type
  ),
  _pTargetWindow(pOwnerEntity->GetOwnerScenePtr()->GetMainWindowPtr()),
  _upDirection(Vector3f(0.0f, 1.0f, 0.0f)),
  _mode(eCameraModes::NORMAL),
  _isOrthoProjectionMatrixCalculated(false),
  _isPerspectiveProjectionMatrixCalculated(false),
  _fov(45.0f),
  _nearPlane(0.1f),
  _farPlane(100.0f)
{

  if (_pTargetWindow == nullptr)
  {
    PUSH_EDITOR_ERROR(eEngineError::MissingPointerToTargetWindowInstance, "Unable to get pointer to target Window instance.", "");
  }
}
Vector3f Camera::GetCameraPosition() const
{
  return GetTransformPtr()->GetPosition();
}

Vector3f Camera::GetCameraDirection() const
{
  return Normalize(GetTransformPtr()->GetZDir());
}


Vector3f Camera::GetPickingRay(int x, int y)
{
  // Dimensions of viewport
  size_t width = _pTargetWindow->GetBufferWidth();
  size_t height = _pTargetWindow->GetBufferHeight();

  // Prepare refs to projection and view matrices for this Camera
  const glm::mat4& projectionMatrix = GetPerspectiveProjectionMatrixConstRef();
  const glm::mat4& viewMatrix = GetViewMatrixConstRef();

  // Get normalised device coordinates
  dfloat normX = static_cast<dfloat>((2 * ((dfloat)x / width)) - 1);
  dfloat normY = static_cast<dfloat>((2 * ((dfloat)y / height)) - 1);
  // Switch Y coordinate because in world it is in opposite fashion
  normY = -normY;

  // Construct vector
  glm::vec3 rayNormalised(normX, normY, 1.0f);
  // Construct ray in Clip Space
  glm::vec4 rayClip(rayNormalised.x, rayNormalised.y, -1.0f, 1.0f);
  // Construct ray in View Space
  glm::vec4 rayEye = inverse(projectionMatrix) * rayClip;
  // Slice it
  rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
  // Construct ray in World Space
  glm::vec4 rayWor4 = inverse(viewMatrix) * rayEye;
  // Slice it
  glm::vec3 rayWorld(rayWor4.x, rayWor4.y, rayWor4.z);
  // Normalize it
  rayWorld = glm::normalize(rayWorld);

  // Return our type vector
  return Vector3f(rayWorld);
}


const glm::mat4& Camera::GetViewMatrixConstRef()
{
  CalculateViewMatrix();

  return _viewMatrix;
}

const glm::mat4& Camera::GetOrthoProjectionMatrixConstRef()
{
  if (!_isOrthoProjectionMatrixCalculated)
  {
    CalculateOrthoProjectionMatrix();
  }

  return _orthoProjectionMatrix;
}

const glm::mat4& Camera::GetPerspectiveProjectionMatrixConstRef()
{
  if (!_isPerspectiveProjectionMatrixCalculated)
  {
    CalculatePerspectiveProjectionMatrix();
  }

  return _perspectiveProjectionMatrix;
}

void Camera::CalculateViewMatrix()
{
  Vector3f position = GetCameraPosition();

  _viewMatrix = glm::lookAt(position.GetData(), (position + GetTransformPtr()->GetZDir()).GetData(), GetTransformPtr()->GetYDir().GetData());
}

void Camera::CalculateOrthoProjectionMatrix()
{
  // Calculate projeciton matrix
  _orthoProjectionMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, _nearPlane, _farPlane);
  _isOrthoProjectionMatrixCalculated = true;
}

void Camera::CalculatePerspectiveProjectionMatrix()
{
  // Calculate projeciton matrix
  _perspectiveProjectionMatrix = glm::perspective(
    static_cast<dfloat>(45.0f * DEG_TO_RAD),
    (GLfloat)(_pTargetWindow->GetBufferWidth()) / _pTargetWindow->GetBufferHeight(),
    _nearPlane, _farPlane
  );

  _isPerspectiveProjectionMatrixCalculated = true;
}