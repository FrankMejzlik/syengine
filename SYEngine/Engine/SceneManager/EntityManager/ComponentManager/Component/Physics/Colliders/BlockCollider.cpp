#include "BlockCollider.h"

#include "Mesh.h"

using namespace SYE;

BlockCollider::BlockCollider(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
  eSlotIndex slotIndex, Component::eType type
):
  Collider(pOwnerEntity, subModulesConstRef, primaryComponentSlots, slotIndex, type)
{
  _type = eType::BLOCK_COLLIDER;

  // Refress all Quick refs
  Refresh();

  // Create new Mesh
  Mesh* pMesh = _pComponentManager->CreateComponent<Mesh>(pOwnerEntity, this);
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
  Mesh* pMesh = _pComponentManager->CreateComponent<Mesh>(_pOwnerEntity, this);
  // Make it desired block
  pMesh->MakeBlock(_width, _height, _length);

  // Add it as Mesh for Collider
  SetMeshPtr(pMesh);
}
