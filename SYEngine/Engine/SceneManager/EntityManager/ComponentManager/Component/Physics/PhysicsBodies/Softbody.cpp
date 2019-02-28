#include "Softbody.h"

#include "BlockCollider.h"

using namespace SYE;

Softbody::Softbody(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
  eSlotIndex slotIndex, Component::eType type
):
  PhysicsBody(pOwnerEntity, subModulesConstRef, primaryComponentSlots, slotIndex, type)
{
}


Softbody::~Softbody() noexcept
{}

BlockCollider* Softbody::AddBlockCollider(dfloat width, dfloat height, dfloat length)
{
  BlockCollider* pBlockCollider = _pComponentManager->CreateComponent<BlockCollider>(_pOwnerEntity, this);
  pBlockCollider->SetDimensions(width, height, length);
  pBlockCollider->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));

  _pCollider = static_cast<Collider*>(pBlockCollider);
    
  return pBlockCollider;
}
