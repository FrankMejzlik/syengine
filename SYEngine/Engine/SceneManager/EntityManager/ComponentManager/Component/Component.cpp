
#include "Component.h"
#include "ComponentManager.h"
#include "Entity.h"

using namespace SYE;



Component::Component(
  Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
  bool isPrimary, bool isActive,
  eSlotIndex slotIndex
) noexcept :
  _pOwnerEntity(pOwnerEntity),
  _subModules(subModulesConstRef),
  _isPrimary(isPrimary),
  _isActive(isActive),
  _isDefault(true),
  _slotIndex(slotIndex),
  _type(eType::COMPONENT)
{
  // Get pointer to ComponentManager that Components can use.
  if (_pOwnerEntity)
  {
    _pComponentManager = pOwnerEntity->GetComponentManagerPtr();
  }

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

bool Component::IsPrimary() const
{
  return _isPrimary;
}

bool Component::SetIsPrimary(bool newValue)
{
  bool oldValue = _isPrimary;
  _isPrimary = newValue;

  return oldValue;
}

bool Component::IsActive() const
{
  return _isActive;
}

bool Component::SetIsActive(bool newValue)
{
  bool oldValue = _isActive;
  _isActive = newValue;

  return oldValue;
}

bool Component::IsDefault() const
{
  return _isDefault;
}

bool Component::SetIsDefault(bool newValue)
{
  bool oldValue = _isDefault;
  _isDefault = newValue;

  return oldValue;
}