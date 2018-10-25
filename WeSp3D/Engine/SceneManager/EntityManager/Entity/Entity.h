#pragma once

#include <map>
#include <memory>

#include <glm/glm.hpp>

#include "macros.h"

namespace WeSp 
{

/**
 * Base class for every entity that can be part of Scene.
 */
class Entity
{

  class Component;
  class Mesh;

public:
  Entity();
  Entity(
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector
  );
  virtual ~Entity();


  size_t GetEntityCount() const;
  size_t GetGUID() const;
  glm::vec3 GetPositionVector() const;
  bool SetPositionVector(const glm::vec3 positionVector);
  glm::vec3 GetRotationVector() const;
  bool SetRotationVector(const glm::vec3 rotationVector);
  glm::vec3 GetScaleVector() const;
  bool SetScaleVector(const glm::vec3 scaleVector);


protected:
  static size_t _entityCounter;
  static size_t _nextGUID;

  // Global Unique ID
  size_t _GUID;
  // Position relative to origin in world
  glm::vec3 _positionVector;
  // Rotation angles in radians by particular axes
  glm::vec3 _rotationVector;
  // Scale factor for every direction
  glm::vec3 _scaleVector;
  // All components attached to this Entity.
  std::map<std::string, std::shared_ptr<Component>> _components;
  std::map<std::string, std::shared_ptr<Mesh>> _meshesToRender;

};

} // namespace WeSp