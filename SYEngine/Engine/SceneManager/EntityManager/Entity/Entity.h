#pragma once

#include <map>
#include <memory>

#include <glm/glm.hpp>

#include "common.h"
#include "IGuidCounted.h"


namespace SYE 
{

class ComponentManager;
class Component;
class Model;

/**
 * Base class for every entity that can be part of Scene.
 *
 * Every Entity MUST have pointer to it's ComponentManager instance.
 */
class Entity:
  public IGuidCounted
{
public:
  Entity() = delete;

  Entity(
    std::shared_ptr<ComponentManager> pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector
  );
  virtual ~Entity();

  void SetBIsToRender(const bool newValue);
  bool GetBIsToRender() const;
  void SetEntityName(std::string name);
  std::string GetEntityName() const;
  size_t GetGUID() const;
  glm::vec3 GetPositionVector() const;
  bool SetPositionVector(const glm::vec3 positionVector);
  glm::vec3 GetRotationVector() const;;
  bool SetRotationVector(const glm::vec3 rotationVector);
  glm::vec3 GetScaleVector() const;
  bool SetScaleVector(const glm::vec3 scaleVector);
  const glm::vec3& GetPositionVectorRefConst() const;
  const glm::vec3& GetRotationVectorRefConst() const;
  const glm::vec3& GetScaleVectorRefConst() const;
  const std::shared_ptr<ComponentManager> GetComponentManager() const;

  std::shared_ptr<Model> GetModel() const { return _pModel; };


protected:
  std::shared_ptr<ComponentManager> _pComponentManager;
  bool _bIsToRender;

  // Global Unique ID
  size_t _GUID;
  std::string _name;
  // Position relative to origin in world
  glm::vec3 _positionVector;
  // Rotation angles in radians by particular axes
  glm::vec3 _rotationVector;
  // Scale factor for every direction
  glm::vec3 _scaleVector;

  // All components attached to this Entity.
  std::map<std::string, std::shared_ptr<Component>> _componentList;
  std::map<std::string, std::shared_ptr<Model>> _modelsToRenderList;
  std::shared_ptr<Model> _pModel;
};

} // namespace SYE