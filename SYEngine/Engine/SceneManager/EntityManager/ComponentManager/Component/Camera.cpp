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


Vector3f Camera::GetPickingRay(size_t x, size_t y) const
{
  // calculate the field-of-view
  float tanFov = 1.0f / _nearPlane;
  float fov = btScalar(2.0) * btAtan(tanFov);
  fov;

  // get a ray pointing forward from the 
  // camera and extend it to the far plane
  btVector3 rayFrom = GetCameraPosition();
  btVector3 rayForward = _pTransform->GetZDir();
  rayForward.normalize();
  rayForward*= _farPlane;

  // find the horizontal and vertical vectors 
  // relative to the current camera view
  btVector3 ver = _upDirection;
  btVector3 hor = rayForward.cross(ver);
  hor.normalize();
  ver = hor.cross(rayForward);
  ver.normalize();
  hor *= 2.f * _farPlane * tanFov;
  ver *= 2.f * _farPlane * tanFov;

  // calculate the aspect ratio
  btScalar aspect = _pTargetWindow->GetBufferWidth() / (btScalar)_pTargetWindow->GetBufferHeight();

  // adjust the forward-ray based on
  // the X/Y coordinates that were clicked
  hor*=aspect;
  btVector3 rayToCenter = rayFrom + rayForward;
  btVector3 dHor = hor * 1.f/float(_pTargetWindow->GetBufferWidth());
  btVector3 dVert = ver * 1.f/float(_pTargetWindow->GetBufferHeight());
  btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * ver;
  rayTo += btScalar(x) * dHor;
  rayTo -= btScalar(y) * dVert;

  // return the final result
  return rayTo;
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