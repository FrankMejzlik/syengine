#include "PhysicsBody.h"

#include "ComponentManager.h"
#include "Collider.h"

using namespace SYE;

PhysicsBody::PhysicsBody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept:
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots),
  _pCollider(nullptr),
  _mass(0.0f),
  _isKinematic(false)
{
  _type = eType::PHYSICS_BODY;
}


PhysicsBody::~PhysicsBody() noexcept
{}

void PhysicsBody::SetCollider(Collider* pCollider)
{
  // Clear old Collider
  ClearCollider();

  _pCollider = pCollider;
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
  _pComponentManager->RemoveComponent(static_cast<Component*>(_pCollider));
  _pCollider = nullptr;
}