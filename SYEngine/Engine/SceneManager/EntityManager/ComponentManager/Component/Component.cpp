
#include "Component.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "PhysicsManager.h"

using namespace SYE;


Component::Component(
  Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
  bool isPrimary, bool isActive,
  eSlotIndex slotIndex, Component::eType type
) :
  _pOwnerEntity(pOwnerEntity),
  _subModules(subModulesConstRef),
  _isPrimary(isPrimary),
  _isActive(isActive),
  _isDefault(true),
  _slotIndex(slotIndex),
  _type(type),
  _primaryComponentSlots(primaryComponentSlots),
  _pOwnerComponent(nullptr)
{
  // If primary Entity
  if (_isPrimary)
  {
    // Enlist self to owner Entity
    _pOwnerEntity->AttachComponent(this);
  }
  else
  {
    // Enlist self to owner Component
    //_pOwnerComponent->EnlistComponent(this);
  }

  // Get pointer to ComponentManager that Components can use.
  if (_pOwnerEntity)
  {
    _pComponentManager = pOwnerEntity->GetComponentManagerPtr();
  }

  // Refress all Quick refs
  Refresh();
}

Component::~Component() noexcept
{
  // Destroy all subcomponents
  // Class specific

  // If primary Entity
  if (_isPrimary)
  {
    // Enlist self to owner Entity
    _pOwnerEntity->DelistComponent(this);
  }
  else
  {
    // Delist self from owner Component
    _pOwnerComponent->DelistComponent(this);
  }
  
}

void Component::SetOwnerComponentPtr(Component* pComponent)
{
  _pOwnerComponent = pComponent;
}

PhysicsManager* Component::GetPhysicsManager()
{
  return _pOwnerEntity->GetPhysicsManager();
}

void Component::Refresh()
{
  // Update all quick refs to sibling Components
}

void Component::SaveComponent()
{
  // Save all changes on this Component
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


bool Component::EnlistComponent(Component* pNewComponent)
{
  UNREFERENCED_PARAMETER(pNewComponent);

  return true;
}

bool Component::DelistComponent(Component* pNewComponent)
{
  UNREFERENCED_PARAMETER(pNewComponent);

  return true;
}
