#pragma once

#include <unordered_map>
#include <memory>
#include <map>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

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

  Entity(ComponentManager* pComponentManager) noexcept;

  virtual ~Entity();

  
  ComponentManager* GetComponentManager();


protected:
  ComponentManager* _pComponentManager;

  /** List of all components on this Entity */
  std::map<size_t, Component*> _components;

  /** Components that should be processed by SceneManager */
  std::map<size_t, Component*> _sceneManagerComponents;

  /** Components that should be processed by EntityManager */
  std::map<size_t, Component*> _entityManagerComponents;

  /** Components that should be processed by InputManager */
  std::map<size_t, Component*> _inputManagerComponents;

  /** Components that should be processed by KeyboardManager */
  std::map<size_t, Component*> _keyboardManagerComponents;

  /** Components that should be processed by MouseManager */
  std::map<size_t, Component*> _mouseManagerComponents;

  /** Components that should be processed by NetworkManager */
  std::map<size_t, Component*> _networkManagerComponents;

  /** Components that should be processed by LogicManager */
  std::map<size_t, Component*> _logicManagerComponents;

  /** Components that should be processed by ScriptManager */
  std::map<size_t, Component*> _scriptComponents;

  /** Components that should be processed by AiManager */
  std::map<size_t, Component*> _aiManagerComponents;

  /** Components that should be processed by SimulationManager */
  std::map<size_t, Component*> _simulationManagerComponents;

  /** Components that should be processed by PhysicsManager */
  std::map<size_t, Component*> _physicsManagerComponents;

  /** Components that should be processed by OutputManager */
  std::map<size_t, Component*> _outputManagerComponents;

  /** Components that should be processed by RenderingManager */
  std::map<size_t, Component*> _renderingManagerComponents;


#if !NEW_SSSEC_IMPLEMENTED
public:

  Entity(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector
  ) noexcept;

  std::string _name;
  bool _bIsToRender;
  bool _bHasColliders;
  void SetBIsToRender(const bool newValue);
  bool GetBIsToRender() const;

  bool GetBHasColliders() const { return _bHasColliders; };

  Collider* AddCollider(Collider* pNewCollider);
  bool DeleteCollider(Collider* pNewCollider);

  const std::unordered_map<size_t, Collider*> &GetColliders() const;


  void SetEntityName(std::string_view name);
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


  // Position relative to origin in world
  glm::vec3 _positionVector;
  // Rotation angles in radians by particular axes
  glm::vec3 _rotationVector;
  // Scale factor for every direction
  glm::vec3 _scaleVector;

  /** All components attached to this Entity */
  std::map<std::string, Component*> _componentList;
  std::map<std::string, Model*> _modelsToRenderList;
  std::unordered_map<size_t, Collider*> _colliders;
  Component* _pModel;

  Component* GetModel() const { return _pModel; };

#endif



};

} // namespace SYE