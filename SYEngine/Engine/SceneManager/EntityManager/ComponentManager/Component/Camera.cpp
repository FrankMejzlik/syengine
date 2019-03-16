#include "Camera.h"

#include <iostream>

#include "Window.h"
#include "Entity.h"
#include "Transform.h"
#include "Texture.h"

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
  _pTargetWindow(nullptr),
  _pTargetTexture(nullptr),
  _upDirection(Vector3f(WORLD_UP_VECTOR)),
  _mode(eCameraModes::NORMAL),
  _isOrthoProjectionMatrixCalculated(false),
  _isPerspectiveProjectionMatrixCalculated(false),
  _fov(CAMERA_FOV),
  _nearPlane(CAMERA_NEAR_PLANE),
  _farPlane(CAMERA_FAR_PLANE)
{}

Vector3f Camera::GetCameraPosition() const
{
  return GetTransformPtr()->GetPosition();
}

Vector3f Camera::GetCameraDirection() const
{
  return Normalize(GetTransformPtr()->GetZDir());
}

void Camera::SetCameraPosition(Vector3f position)
{
  GetTransformPtr()->SetPosition(position);
}

void Camera::SetCameraDirection(Vector3f direction)
{
  UNREFERENCED_PARAMETER(direction);

  LOG_NOT_IMPLEMENTED;
  //GetTransformPtr()->SetDirection(direction);
}

Vector3f Camera::GetPickingRay(int x, int y)
{
  // Dimensions of viewport
  size_t width = _pTargetWindow->GetBufferWidth();
  size_t height = _pTargetWindow->GetBufferHeight();

  // Prepare refs to projection and view matrices for this Camera
  const glm::mat4& projectionMatrix = dc_GetPerspectiveProjectionMatrixConstRef();
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



const Matrix4f& Camera::GetOrthogonalProjectionMatrix() const
{
  return _orthogonalProjectionMatrix;
}

void Camera::SetOrthogonalProjectionMatrix(Matrix4f matrix)
{
  _orthogonalProjectionMatrix = matrix;

  _isOrthoProjectionMatrixCalculated = false;
}

void Camera::SetTargetWindow(Window* pWindow) 
{
  _pTargetTexture = nullptr;
  _pTargetWindow = pWindow;

  _isPerspectiveProjectionMatrixCalculated = false;
  _isOrthoProjectionMatrixCalculated = false;
}

void Camera::SetTargetTexture(const Texture* pTexture) 
{
  _pTargetWindow = nullptr;
  _pTargetTexture = pTexture;

  _isPerspectiveProjectionMatrixCalculated = false;
  _isOrthoProjectionMatrixCalculated = false;
}

const glm::mat4& Camera::GetViewMatrixConstRef()
{
  dc_CalculateViewMatrix();

  return _dc_viewMatrix;
}

const glm::mat4& Camera::dc_GetOrthoProjectionMatrixConstRef()
{
  if (!_isOrthoProjectionMatrixCalculated)
  {
    dc_CalculateOrthoProjectionMatrix();
  }

  return _dc_orthoProjectionMatrix;
}

const glm::mat4& Camera::dc_GetPerspectiveProjectionMatrixConstRef()
{
  if (!_isPerspectiveProjectionMatrixCalculated)
  {
    dc_CalculatePerspectiveProjectionMatrix();
  }

  return _dc_perspectiveProjectionMatrix;
}

void Camera::dc_CalculateViewMatrix()
{
  Vector3f position = GetCameraPosition();

  _dc_viewMatrix = glm::lookAt(position.GetData(), (position + GetTransformPtr()->GetZDir()).GetData(), GetTransformPtr()->GetYDir().GetData());
}

void Camera::dc_CalculateOrthoProjectionMatrix()
{
  // Calculate projeciton matrix
  _dc_orthoProjectionMatrix = glm::ortho(
    MAIN_CAMERA_ORTHO_FOV_LEFT, MAIN_CAMERA_ORTHO_FOV_RIGHT, 
    MAIN_CAMERA_ORTHO_FOV_BOTTOM, MAIN_CAMERA_ORTHO_FOV_UP, 
    _nearPlane, _farPlane
  );

  _isOrthoProjectionMatrixCalculated = true;
}

void Camera::dc_CalculatePerspectiveProjectionMatrix()
{
  // If rendering to window
  if (_pTargetWindow)
  {
    // Calculate projeciton matrix
    _dc_perspectiveProjectionMatrix = glm::perspective(
      CAMERA_FOV,
      (GLfloat)(_pTargetWindow->GetBufferWidth()) / _pTargetWindow->GetBufferHeight(),
      _nearPlane, _farPlane
    );
  }

  // If rendering to texture
  if (_pTargetTexture)
  {
    _dc_perspectiveProjectionMatrix = glm::perspective(
      CAMERA_FOV,
      (GLfloat)RENDER_TO_TEXTURE_WIDTH / RENDER_TO_TEXTURE_HEIGHT,
      _nearPlane, _farPlane
    );
  }

  _isPerspectiveProjectionMatrixCalculated = true;
}