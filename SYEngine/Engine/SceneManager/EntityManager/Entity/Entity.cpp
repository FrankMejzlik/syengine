#include "Entity.h"
#include "Collider/Collider.h"


using namespace SYE;

Entity::Entity(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector,
  glm::vec3 rotationVector,
  glm::vec3 scaleVector
):
  _pComponentManager(pComponentManager),
  _positionVector(positionVector),
  _rotationVector(rotationVector),
  _scaleVector(scaleVector),
  _bIsToRender(false),
  _bHasColliders(false)
{

}

Entity::~Entity() 
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

ComponentManager* Entity::GetComponentManager()
{
  return _pComponentManager;
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