#pragma once

#include <array>
#include <map>

#include "common.h"

namespace SYE 
{

// Forward declarations
class Component;
class Transform;
class PhysicsBody;
class Rigidbody;
class Softbody;
class MeshRenderer;
class PointLight;
class ScriptHandler;

/**
 * Interface for classes that needs to access EngineContext data
 *
 * This class is NOT responsible for allocation, only provides common API to it.
 */
class IComponentsInterface
{
public:
 
  IComponentsInterface() = delete;
  IComponentsInterface(std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentOnEntity);


  void RefreshQuickRefs();

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& GetPrimaryComponentSlotsRef()
  {
    return _primaryComponentOnEntity;
  }

  Transform* GetTransformPtr() const;
  PhysicsBody* GetPhysicsBody() const;
  Rigidbody* GetRigidbodyPtr() const;
  Softbody* GetSoftbodyPtr() const;
  MeshRenderer* GetMeshRendererPtr() const;
  PointLight* GetPointLightPtr() const;
  ScriptHandler* GetFirstScriptHandlerPtr() const;
  std::map<size_t, Component*>& GetScriptHandlersRef();

private:
  /**
   * Reference to table of active primary Components on owning Entity
   *
   * Indices of slots are configured at config_components.h.
   * Some slots are singletons, e.g. there can be only one light source per Component.
   */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& _primaryComponentOnEntity;

  // Singletons
  Transform* _pTransform;
  PhysicsBody* _pPhysicsBody;
  MeshRenderer* _pMeshRenderer;
  PointLight* _pPointLight;

  // Multitons
  std::map<size_t, Component*> _pScriptHandlers;
};

}