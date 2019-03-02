
#include "SphereCollider.h"
#include "ComponentManager.h" 

#include "Mesh.h"

using namespace SYE;

SphereCollider::SphereCollider(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Collider(pOwnerEntity, pOwnerComponent, slotIndex, type)
{
  // Create new Mesh
  Mesh* pMesh = GetComponentManagerPtr()->CreateComponent<Mesh>(pOwnerEntity, this);
  // Make it  default sphere
  pMesh->MakeSphere(1.0f, 20ULL, 20ULL);

  // Add it as Mesh for Collider
  SetMeshPtr(pMesh);
}

void SphereCollider::SetDimensions(dfloat radius, size_t numSlices, size_t numStacks)
{
  // Save dimensions
  _radius = radius;
  _numSlices = numSlices;
  _numStacks = numStacks;

  // Clear old Mesh
  ClearMesh();

  // Create new Mesh
  Mesh* pMesh = GetComponentManagerPtr()->CreateComponent<Mesh>(_pOwnerEntity, this);
  // Make it desired sphere
  pMesh->MakeSphere(_radius, _numSlices, _numStacks);

  // Add it as Mesh for Collider
  SetMeshPtr(pMesh);
}
