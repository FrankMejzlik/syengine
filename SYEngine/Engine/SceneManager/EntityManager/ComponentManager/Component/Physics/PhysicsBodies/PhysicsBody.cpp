#include "PhysicsBody.h"

#include "ComponentManager.h"
#include "Collider.h"

#include "Scene.h"
#include "PhysicsScene.h"
#include "Transform.h"
#include "PhysicsEntity.h"
#include "ScriptHandler.h"
#include "Script.h"

using namespace SYE;

PhysicsBody::PhysicsBody(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Component(
    pOwnerEntity, pOwnerComponent,
    true, true, 
    slotIndex, type
    ),
  _pCollider(nullptr),
  _mass(0.0f),
  _isKinematic(false),
  _restitution(0.6f),
  _tag(0ULL)
{}


PhysicsBody::~PhysicsBody() noexcept
{
  // Try to delete this existing PhysicsEntity (if exists)
  GetOwnerScenePtr()->GetPhysicsScenePtr()->RemovePhysicsEntity(this);
}

void PhysicsBody::SetTag(size_t tag)
{
  _tag = tag;
}

size_t PhysicsBody::GetTag() const
{
  return _tag;
}

void PhysicsBody::TriggerOnCollision(const Collision& collision)
{
  auto scriptHandlers = GetScriptHandlersRef();

  // Loop through all ScriptHandlers and trigger their collision methods
  for (auto&& scriptHandlerPair : scriptHandlers)
  {
    ScriptHandler* pSH = static_cast<ScriptHandler*>(scriptHandlerPair.second);

    pSH->GetAttachedScriptPtr()->OnCollision(collision);
  }
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

void PhysicsBody::SaveComponent()
{
  // Try to delete this existing PhysicsEntity (if exists)
  GetOwnerScenePtr()->GetPhysicsScenePtr()->RemovePhysicsEntity(this);

  // Create new updated Physics Entity
  GetOwnerScenePtr()->GetPhysicsScenePtr()->InsertPhysicsEntity(this);
}

void PhysicsBody::SetRestitution(dfloat newValue)
{
  _restitution = newValue;
  _pPhysEntity->SetRestitution(newValue);
}

dfloat PhysicsBody::GetRestitution() const
{
  return _restitution;
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


void PhysicsBody::SetToContiniousCollision()
{
  _pPhysEntity->SetCccThreshold();
}

void PhysicsBody::SetIsKinematic(bool isKinematic)
{
  _isKinematic = isKinematic;

  _pPhysEntity->SetKinematic();

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
  GetComponentManagerPtr()->DestroyComponent(static_cast<Component*>(_pCollider));
  _pCollider = nullptr;
}