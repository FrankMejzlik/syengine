#include "Rigidbody.h"

#include "BlockCollider.h"

using namespace SYE;

Rigidbody::Rigidbody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept:
  PhysicsBody(pOwnerEntity, subModulesConstRef, primaryComponentSlots)
{
  _type = eType::RIGID_BODY;
}


Rigidbody::~Rigidbody() noexcept
{}

BlockCollider* Rigidbody::AddBlockCollider(dfloat width, dfloat height, dfloat length)
{
  BlockCollider* pBlockCollider = _pComponentManager->CreateComponent<BlockCollider>(_pOwnerEntity);
  pBlockCollider->SetDimensions(width, height, length);
  pBlockCollider->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));

  _pCollider = static_cast<Collider*>(pBlockCollider);
    
  return pBlockCollider;
}