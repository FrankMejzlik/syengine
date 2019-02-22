#include "Entity.h"
#include "Collider.h"


using namespace SYE;

Entity::Entity(Scene* pOwnerScene, ComponentManager* pComponentManager) noexcept :
  _pParent(nullptr),
  _pOwnerScene(pOwnerScene),
  _isStatic(true),
  _pComponentManager(pComponentManager),
  _type(Entity::eType::WORLD)
{}

Entity::~Entity() 
{}

ComponentManager* Entity::GetComponentManagerPtr()
{
  return _pComponentManager;
}

Entity::eType Entity::SetType(eType newValue)
{
  Entity::eType oldType = _type;
  _type = newValue;

  return oldType;
}

Entity::eType Entity::GetType() const
{
  return _type;
}

Entity* Entity::SetParent(Entity* newValue)
{
  Entity* oldParent = _pParent;
   _pParent = newValue;

  return oldParent;
}

Entity* Entity::GetParentPtr() const 
{ 
  return _pParent; 
}

void Entity::AddChild(Entity* pNewChild)
{
  _children.insert(std::pair(pNewChild->GetGuid(), pNewChild));
}

void Entity::RemoveChild(Entity* pNewChild)
{
  _children.erase(pNewChild->GetGuid());
}

const std::map<size_t, Entity*> Entity::GetChildren() const 
{ 
  return _children; 
}

void Entity::RefreshComponents()
{
  for (auto&& component : _components)
  {
    component.second->Refresh();
  }
}

