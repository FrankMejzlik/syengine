#include "Collider.h"

using namespace SYE;

Collider::Collider(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots):
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true,
    PHYSICS_COLLIDER
  )
{
  _type = eType::COLLIDER;
}


Collider::~Collider()
{}
