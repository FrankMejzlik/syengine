#include "Rigidbody.h"

using namespace SYE;

Rigidbody::Rigidbody(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept:
  Component(pOwnerEntity, subModulesConstRef)
{
  _type = eType::RIGIDBODY;
}


Rigidbody::~Rigidbody() noexcept
{}
