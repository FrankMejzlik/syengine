#include "Camera.h"

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
  
  _mode(eCameraModes::NORMAL)
{
  _type = eType::CAMERA;
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

}