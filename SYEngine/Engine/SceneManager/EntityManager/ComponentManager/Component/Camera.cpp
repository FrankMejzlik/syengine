#include "Camera.h"

#include <iostream>

#include "Window.h"
#include "Entity.h"
#include "Transform.h"

using namespace SYE;

Camera::Camera(
  Entity* pOwnerEntity,
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
) noexcept :
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true,
    CAMERA
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
  _type = eType::CAMERA;

  if (_pTargetWindow == nullptr)
  {
    PUSH_EDITOR_ERROR(eEngineError::MissingLogicalDependency, "Unable to get pointer to target Window instance.", "");
  }
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

Vector3f Camera::GetCameraPosition() const
{
  return _pTransform->GetPosition();
}

Vector3f Camera::GetCameraDirection() const
{
  return Normalize(_pTransform->GetZDir());
}


Vector3f Camera::GetPickingRay(int x, int y)
{
  // Dimensiions 
  size_t width = _pTargetWindow->GetBufferWidth();
  size_t height = _pTargetWindow->GetBufferHeight();

  const glm::mat4& projectionMatrix = GetPerspectiveProjectionMatrixConstRef();
  const glm::mat4& viewMatrix = GetViewMatrixConstRef();


  // Normalised device coordinates
  dfloat normX = static_cast<dfloat>((2 * ((dfloat)x / width)) - 1);
  dfloat normY = static_cast<dfloat>((2 * ((dfloat)y / height)) - 1);
  normY = -normY;
  dfloat normZ = 1.0f;

  glm::vec3 rayNormalised(normX, normY, normZ);

  glm::vec4 rayClip(rayNormalised.x, rayNormalised.y, -1.0f, 1.0f);

  glm::vec4 rayEye = inverse(projectionMatrix) * rayClip;

  rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

  glm::vec4 rayWor4 = inverse(viewMatrix) * rayEye;

  glm::vec3 rayWorld(rayWor4.x, rayWor4.y, rayWor4.z);
  rayWorld = glm::normalize(rayWorld);

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

  _viewMatrix = glm::lookAt(position.GetData(), (position + _pTransform->GetZDir()).GetData(), _pTransform->GetYDir().GetData());
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