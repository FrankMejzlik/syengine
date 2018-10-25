#include "Entity.h"

using namespace WeSp;

// Initialize static attributes
size_t Entity::_entityCounter(0);
size_t Entity::_nextGUID(0);


Entity::Entity() :
  _GUID(_nextGUID),
  _positionVector(0.0f, 0.0f, 0.0f),
  _rotationVector(0.0f, 0.0f, 0.0f),
  _scaleVector(1.0f, 1.0f, 1.0f)
{
  // Increment counters
  ++_entityCounter;
  ++_nextGUID;
}
Entity::Entity(
  glm::vec3 positionVector,
  glm::vec3 rotationVector,
  glm::vec3 scaleVector
):
  _GUID(_nextGUID),
  _positionVector(positionVector),
  _rotationVector(rotationVector),
  _scaleVector(scaleVector)
{
  // Increment counters
  ++_entityCounter;
  ++_nextGUID;
}

Entity::~Entity() 
{
  // Decrement entity counter
  --_entityCounter;
}

size_t Entity::GetEntityCount() const
{
  return _entityCounter;
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