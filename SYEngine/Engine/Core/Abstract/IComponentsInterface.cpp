
#include "IComponentsInterface.h"

#include "Transform.h"
#include "PhysicsBody.h"
#include "Rigidbody.h"
#include "Softbody.h"

using namespace SYE;

IComponentsInterface::IComponentsInterface(std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentOnEntity) :
  _primaryComponentOnEntity(primaryComponentOnEntity)
{}


void IComponentsInterface::RefreshQuickRefs()
{
  // Update all Component type quick refs

  if (!_primaryComponentOnEntity[COMPONENT_TRANSFORM_SLOT].empty())
  {
    _pTransform = static_cast<Transform*>(_primaryComponentOnEntity[COMPONENT_TRANSFORM_SLOT].begin()->second);
  }

  if (!_primaryComponentOnEntity[COMPONENT_PHYSICS_BODY_SLOT].empty())
  {
    _pPhysicsBody = static_cast<PhysicsBody*>(_primaryComponentOnEntity[COMPONENT_PHYSICS_BODY_SLOT].begin()->second);
  }

}

Transform* IComponentsInterface::GetTransformPtr() const
{
  return _pTransform;
}

PhysicsBody* IComponentsInterface::GetPhysicsBody() const
{
  return _pPhysicsBody;
}

Rigidbody* IComponentsInterface::GetRigidbodyPtr() const
{
  return dynamic_cast<Rigidbody*>(_pPhysicsBody);
}

Softbody* IComponentsInterface::GetSoftbodyPtr() const
{
  return dynamic_cast<Softbody*>(_pPhysicsBody);
}