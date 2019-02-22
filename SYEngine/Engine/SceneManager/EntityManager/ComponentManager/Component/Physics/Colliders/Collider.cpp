#include "Collider.h"

#include "ComponentManager.h"

#include "Mesh.h"
#include "Rigidbody.h"
#include "Transform.h"

using namespace SYE;

Collider::Collider(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
) noexcept:
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true,
    PHYSICS_COLLIDER
  )
{
  _type = eType::COLLIDER;
}

Collider::~Collider() noexcept
{
  // Set your Mesh free
  ClearMesh();
}

void Collider::Refresh()
{
  // Update Transform quick ref
  if (!_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].empty())
  {
    _pTransform = static_cast<Transform*>(_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].begin()->second);
  }

  // Update Rigidbody quick ref
  if (!_primaryComponentSlots[COMPONENT_PHYSICS_BODY_SLOT].empty())
  {
    _pRigidbody = static_cast<Rigidbody*>(_primaryComponentSlots[COMPONENT_PHYSICS_BODY_SLOT].begin()->second);
  }

}

void Collider::SetMeshPtr(Mesh* pMesh)
{
  _pMesh = pMesh;
}

void Collider::ClearMesh()
{
  // Tell ComponentManager to remove it
  _pComponentManager->RemoveComponent(_pMesh);

  // Set to nullptr
  _pMesh = nullptr;
}

const std::vector<unsigned int>& Collider::GetIndices() const
{
  return _pMesh->GetIndices();
}

const std::vector<dfloat>& Collider::GetVertices() const
{
  return _pMesh->GetVertices();
}

const Vector3f& Collider::GetWorldPositionConstRef() const
{
  return _worldPosition;
}

const Vector3f& Collider::GetWorldRotationConstRef() const
{
  return _worldRotation;
}

const Vector3f& Collider::GetWorldScaleConstRef() const
{
  return _worldScale;
}

bool Collider::IsTrigger() const 
{ 
  return _isTrigger; 
}

void Collider::RecalculateAbsolutePosition()
{
  _worldPosition = _pTransform->GetPosition() + _localPosition;
}

void Collider::RecalculateAbsoluteRotation()
{
  _worldRotation = _pTransform->GetRotation() + _localRotation;
}