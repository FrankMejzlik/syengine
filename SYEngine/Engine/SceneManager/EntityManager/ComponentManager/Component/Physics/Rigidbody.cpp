#include "Rigidbody.h"

using namespace SYE;

Rigidbody::Rigidbody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept:
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots)
{
  _type = eType::RIGIDBODY;
}


Rigidbody::~Rigidbody() noexcept
{}
