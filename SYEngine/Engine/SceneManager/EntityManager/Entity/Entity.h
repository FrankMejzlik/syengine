#pragma once

#include <unordered_map>
#include <memory>
#include <map>


#include <glm/glm.hpp>

#include "common.h"
#include "IGuidCounted.h"

namespace SYE 
{
class Collider;
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
    ComponentManager* pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector
  );
  virtual ~Entity();

  void SetBIsToRender(const bool newValue);
  bool GetBIsToRender() const;

  bool GetBHasColliders() const { return _bHasColliders; };

  Collider* AddCollider(Collider* pNewCollider);
  bool DeleteCollider(Collider* pNewCollider);

  const std::unordered_map<size_t, Collider*> &GetColliders() const;


  void SetEntityName(std::string name);
  std::string GetEntityName() const;
  glm::vec3 GetPositionVector() const;
  bool SetPositionVector(const glm::vec3 positionVector);
  glm::vec3 GetRotationVector() const;;
  bool SetRotationVector(const glm::vec3 rotationVector);
  glm::vec3 GetScaleVector() const;
  bool SetScaleVector(const glm::vec3 scaleVector);
  const glm::vec3& GetPositionVectorRefConst() const;
  const glm::vec3& GetRotationVectorRefConst() const;
  const glm::vec3& GetScaleVectorRefConst() const;
  ComponentManager* GetComponentManager();

  Component* GetModel() const { return _pModel; };


protected:
  ComponentManager* _pComponentManager;
  bool _bIsToRender;
  bool _bHasColliders;

  std::string _name;
  // Position relative to origin in world
  glm::vec3 _positionVector;
  // Rotation angles in radians by particular axes
  glm::vec3 _rotationVector;
  // Scale factor for every direction
  glm::vec3 _scaleVector;

  // All components attached to this Entity.
  std::map<std::string, Component*> _componentList;
  std::map<std::string, Model*> _modelsToRenderList;
  std::unordered_map<size_t, Collider*> _colliders;
  Component* _pModel;

};

} // namespace SYE