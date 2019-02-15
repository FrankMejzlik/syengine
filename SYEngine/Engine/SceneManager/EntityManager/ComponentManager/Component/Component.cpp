
#include "Component.h"

using namespace SYE;


Component::Component(Entity* pOwnerEntity) noexcept :
  _pOwnerEntity(pOwnerEntity)
{
}


Entity* Component::GetOwnerEntityPtr() const
{
  return _pOwnerEntity;
};

Entity* Component::SetOwnerEntityPtr(Entity* newOwnerPtr)
{
  Entity* oldOwner = _pOwnerEntity;
  _pOwnerEntity = newOwnerPtr;

  return oldOwner;
}

bool Component::GetIsPrimary() const
{
  return _isPrimary;
}

bool Component::SetIsPrimary(bool newValue)
{
  bool oldValue = _isPrimary;
  _isPrimary = newValue;

  return oldValue;
}