#include "Entity.h"

using namespace WeSp;

Entity::Entity(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector,
  glm::vec3 rotationVector,
  glm::vec3 scaleVector
):
  _pComponentManager(pComponentManager),
  _positionVector(positionVector),
  _rotationVector(rotationVector),
  _scaleVector(scaleVector),
  _bIsToRender(false)
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

void Entity::SetEntityName(std::string name)
{
  _name = name;
  return;
}

size_t Entity::GetGUID() const
{
  return _GUID;
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

const std::shared_ptr<ComponentManager> Entity::GetComponentManager() const
{
  return _pComponentManager;
}
