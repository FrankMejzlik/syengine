#include "Entity.h"
#include "Collider.h"


using namespace SYE;

Entity::Entity(Scene* pOwnerScene, ComponentManager* pComponentManager) noexcept :
  _pParent(nullptr),
  _pTransform(nullptr),
  _pOwnerScene(pOwnerScene),
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

#if !NEW_SSSEC_IMPLEMENTED

Entity::Entity(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector,
  glm::vec3 rotationVector,
  glm::vec3 scaleVector
) noexcept :
  _pComponentManager(pComponentManager),
  _positionVector(positionVector),
  _rotationVector(rotationVector),
  _scaleVector(scaleVector),
  _bIsToRender(false),
  _bHasColliders(false)
{

}

void Entity::SetBIsToRender(const bool newValue)
{
  _bIsToRender = newValue;
}

bool Entity::GetBIsToRender() const
{
  return _bIsToRender;
}

void Entity::SetEntityName(std::string_view name)
{
  _name = name;
  return;
}


glm::vec3 Entity::GetPositionVector() const
{
  return _positionVector;
}

bool Entity::SetPositionVector(const glm::vec3 positionVector)
{
  _positionVector = positionVector;
  return true;
}

glm::vec3 Entity::GetRotationVector() const
{
  return _rotationVector;
}

bool Entity::SetRotationVector(const glm::vec3 rotationVector)
{
  _rotationVector = rotationVector;
  return true;
}

glm::vec3 Entity::GetScaleVector() const
{
  return _scaleVector;
}

bool Entity::SetScaleVector(const glm::vec3 scaleVector)
{
  _scaleVector = scaleVector;
  return true;
}

std::string Entity::GetEntityName() const
{
  return _name;
}

const glm::vec3& Entity::GetPositionVectorRefConst() const
{
  return _positionVector;
}

const glm::vec3& Entity::GetRotationVectorRefConst() const
{
  return _rotationVector;
}

const glm::vec3& Entity::GetScaleVectorRefConst() const
{
  return _scaleVector;
}



const std::unordered_map<size_t, Collider*> &Entity::GetColliders() const
{
  return _colliders;
}

Collider* Entity::AddCollider(Collider* pNewCollider)
{
  _colliders.insert(std::make_pair(pNewCollider->GetGuid(), pNewCollider));

  _bHasColliders = true;

  return pNewCollider; 
}

bool Entity::DeleteCollider(Collider* pNewCollider)
{
  auto result = _colliders.erase(pNewCollider->GetGuid()); result;

  if (_colliders.empty())
  {
    _bHasColliders = false;
  }
  return true; 
}



#endif