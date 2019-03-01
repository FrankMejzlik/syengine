#include "BlockCollider.h"

#include "Mesh.h"

using namespace SYE;

BlockCollider::BlockCollider(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Collider(pOwnerEntity, pOwnerComponent, slotIndex, type)
{
  // Create new Mesh
  Mesh* pMesh = GetComponentManagerPtr()->CreateComponent<Mesh>(pOwnerEntity, this);
  // Make it  default block
  pMesh->MakeBlock(1.0f, 1.0f, 1.0f);

  // Add it as Mesh for Collider
  SetMeshPtr(pMesh);

}

void BlockCollider::SetDimensions(dfloat width, dfloat height, dfloat length)
{
  // Save dimensions
  _width = width;
  _height = height;
  _length = length;

  // Clear old Mesh
  ClearMesh();

  // Create new Mesh
  Mesh* pMesh = GetComponentManagerPtr()->CreateComponent<Mesh>(_pOwnerEntity, this);
  // Make it desired block
  pMesh->MakeBlock(_width, _height, _length);

  // Add it as Mesh for Collider
  SetMeshPtr(pMesh);
}
