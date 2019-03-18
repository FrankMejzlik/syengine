
#include "Component.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "PhysicsManager.h"

using namespace SYE;


Component::Component(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  bool isPrimary, bool isActive,
  eSlotIndex slotIndex, Component::eType type
) :
  IEngineContextInterface(pOwnerEntity->GetEngineContextPtr()),
  ISceneContextInterface(pOwnerEntity->GetSceneContextPtr()),
  IComponentsInterface(pOwnerEntity->GetPrimaryComponentSlotsRef()),
  _pOwnerScene(pOwnerEntity->GetOwnerScenePtr()),
  _pOwnerEntity(pOwnerEntity),
  _pOwnerComponent(pOwnerComponent),
  _isPrimary(isPrimary),
  _isActive(isActive),
  _slotIndex(slotIndex),
  _type(type)
{
  // Refress all Quick refs
  RefreshQuickRefs();
}

Component::~Component() noexcept
{
  // If attached to Entity, detach self from it
  if (_pOwnerEntity != nullptr)
  {
    _pOwnerEntity->DetachComponent(this);
  }
  

  //! \todo Pot Component specific Subcomponents into container to allow their generic destruction
}

void Component::ResetOwnerPointers()
{
  _pOwnerEntity = nullptr;
  _pOwnerComponent = nullptr;
  _pOwnerScene = nullptr;
}

void Component::SetOwnerComponentPtr(Component* pComponent)
{
  _pOwnerComponent = pComponent;
}


void Component::SaveComponent()
{
  // Refresh quick links
  RefreshQuickRefs();
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

Scene* Component::GetOwnerScenePtr() const 
{
  if (_pOwnerEntity == nullptr)
  {
    return nullptr;
  }

  return _pOwnerEntity->GetOwnerScenePtr(); 
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
