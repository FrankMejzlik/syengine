#include "PhysicsBody.h"

#include "ComponentManager.h"
#include "Collider.h"

#include "Scene.h"
#include "PhysicsScene.h"
#include "Transform.h"

using namespace SYE;

PhysicsBody::PhysicsBody(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
  eSlotIndex slotIndex, Component::eType type
):
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true, 
    slotIndex, type
    ),
  _pCollider(nullptr),
  _mass(0.0f),
  _isKinematic(false)
{
}

void PhysicsBody::SetCollider(Collider* pCollider)
{
  // Clear old Collider
  ClearCollider();

  _pCollider = pCollider;
}

void PhysicsBody::SetPhysicsEntity(PhysicsEntity* pPhysEntity)
{
  _pPhysEntity = pPhysEntity;
}

void PhysicsBody::Refresh()
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


void PhysicsBody::SaveComponent()
{
  // Try to delete this existing PhysicsEntity (if exists)
  GetOwnerScenePtr()->GetPhysicsScenePtr()->RemovePhysicsEntity(this);

  // Create new updated Physics Entity
  GetOwnerScenePtr()->GetPhysicsScenePtr()->InsertPhysicsEntity(this);
}

PhysicsEntity* PhysicsBody::GetPhysicsEntity() const
{
  return _pPhysEntity;
}

bool PhysicsBody::HasCollider() const
{
  if (_pCollider == nullptr)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void PhysicsBody::SetMass(dfloat mass)
{
  _mass = mass;
}

bool PhysicsBody::IsStatic() const
{
  if (_mass <= 0.0f && !_isKinematic)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool PhysicsBody::IsKinematic() const
{
  if (_mass <= 0.0f && _isKinematic)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void PhysicsBody::SetIsKinematic(bool isKinematic)
{
  _isKinematic = isKinematic;
}

bool PhysicsBody::IsDynamic() const
{
  if (_mass > 0.0f)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void PhysicsBody::ClearCollider()
{
  // Detroy Collider
  _pComponentManager->DestroyComponent(static_cast<Component*>(_pCollider));
  _pCollider = nullptr;
}