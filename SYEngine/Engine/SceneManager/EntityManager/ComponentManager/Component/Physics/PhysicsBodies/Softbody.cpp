#include "Softbody.h"

#include "BlockCollider.h"

using namespace SYE;

Softbody::Softbody(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  PhysicsBody(pOwnerEntity, pOwnerComponent, slotIndex, type)
{
}


Softbody::~Softbody() noexcept
{}

BlockCollider* Softbody::AddBlockCollider(dfloat width, dfloat height, dfloat length)
{
  BlockCollider* pBlockCollider = GetComponentManagerPtr()->CreateComponent<BlockCollider>(_pOwnerEntity, this);
  pBlockCollider->SetDimensions(width, height, length);
  pBlockCollider->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));

  _pCollider = static_cast<Collider*>(pBlockCollider);
    
  return pBlockCollider;
}
