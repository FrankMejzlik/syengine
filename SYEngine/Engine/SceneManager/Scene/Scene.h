#pragma once

#include <memory>
#include <string>
#include <map>
#include <unordered_map>
#include <array>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "IEngineContextInterface.h"
#include "IErrorLogging.h"
#include "IGuidCounted.h"
#include "SceneContext.h"

#include "MathLibrary.h"


namespace SYE
{

class Camera;
class Window;
class PhysicsScene;
class PhysicsBody;
class Entity;
class Component;
class Engine;

/**
 * Every Scene MUST have it's EntityController to call to.
 */
class Scene:
  public IGuidCounted, public IErrorLogging, public IEngineContextInterface
{
  // Methods
public:
  Scene() = delete;
  Scene(EngineContext* pEngineContext, Engine* pEngine, Window* pTargetWindow, size_t sceneId);
  ~Scene() noexcept;

  /*!
   * Adds Entity to this Scene behaving like standard Camera
   * 
   * PRIMARY COMPONENTS:
   *  \ref SYE::Transform
   *  \ref SYE::Camera
   * 
   * \param positionVector  Position of camera. 
   * \param initialYaw  Initial yaw angle (in degrees) camera will start with.
   * \param startPitch  Initial pitch angle (in degrees) camera will start with.
   *    @note  Yaw, pitch and roll are applied always in order yaw, pitch, roll.
   * \return  Pointer to newly added Entity.
   */
  Entity* AddCamera(
    Vector3f positionVector, 
    dfloat initialYaw, dfloat initialPitch
  );

  /*!
   * Adds to this Scene Entity representing terrain
   * 
   * PRIMARY COMPONENTS:
   *  \ref SYE::Transform
   *  \ref SYE::MeshRenderer
   * 
   * \param positionVector
   * \param rotationVector
   * \param scaleVector
   * \param vertices
   * \param indices
   * \return  Pointer to newly added Entity.
   */
  Entity* AddTerrain(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    std::vector<dfloat> vertices, std::vector<unsigned int> indices
  );


  Entity* AddQuad(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    dfloat width, dfloat height,
    bool isStatic
  );


  /**
   * Creates Entity representing block
   *
   * PRIMARY COMPONENTS:
   *    @ref SYE::Transform
   *    @ref SYE::MeshRenderer
   *    @ref SYE::Rigidbody
   */
  Entity* AddBlock(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    dfloat width, dfloat height, dfloat length,
    bool isStatic = true,
    dfloat mass = 0.0f
  );

  /**
   * Creates prism that is defined by 8 vertices in model space
   *
   * Default origin point is p1.
   *
   * VERTEX ORDER:
   *      p4 ------ p3      p8 ------ p7
   *  +X: |         |   -X: |         |
   *      |         |       |         |
   *      p1 ------ p2      p5 ------ p6
   */
  Entity* AddPrism(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    Vector3f origin,
    const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
    const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8,
    bool isStatic = true,
    dfloat mass = 0.0f
  );

  Entity* AddSphere(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    dfloat radius, size_t numSlices, size_t numStacks,
    bool isStatic = true,
    dfloat mass = 0.0f
  );

  Entity* AddDirectionalLight(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
    Vector3f direction,
    bool isStatic = true
  );

  Entity* AddPointLight(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
    dfloat nearPlane, dfloat farPlane,
    Vector3f coefficients,
    bool isStatic = true
  );

  Entity* AddSpotLight(
    Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
    Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
    dfloat nearPlane, dfloat farPlane,
    Vector3f coefficients,
    Vector3f direction,
    dfloat coneAngle,
    bool isStatic = true
  );



  template <typename EntityType>
  EntityType* AddEntity()
  {
    // Spawn new Entity
    EntityType* pNewEntity = GetEntityManagerPtr()->CreateEntity<EntityType>(this, nullptr);

    // Try to attach it to self
    if (!AttachEntity(pNewEntity))
    {
      PUSH_EDITOR_ERROR(
        eEngineError::AddingEntityToSceneFailed,
        "Adding Entity '" + std::to_string(pNewEntity->GetGuid()) + "' to Scene '" + std::to_string(GetGuid()) + "' failed.",
        ""
      );

      // Detroy this Entity
      GetEntityManagerPtr()->DestroyEntity(pNewEntity);

      return nullptr;
    }

    return pNewEntity;
  }

  bool RemoveEntity(Entity* pEntityToDelete);

  /**
   * Casts ray from specified position in specified direction and returns <PBody hit, hit Point>
   */
  std::pair<PhysicsBody*, Vector3f> Raycast(Vector3f from, Vector3f direction) const;

  Camera* GetEditorCamera() const;

  void SetMainWindowPtr(Window* pMainWindow) { _pMainWindow = pMainWindow; };
  Window* GetMainWindowPtr() const { return _pMainWindow; };

  void SetPhysicsScenePtr(PhysicsScene* pPhysicsScene);
  PhysicsScene* GetPhysicsScenePtr() const;

  SceneContext* GetSceneContextPtr() const { return _pSceneContext.get(); };


  /** Active Components categorized to important slots based on what module needs to acces them. */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> GetActivePrimaryComponentSlotsRef() { return _activeComponentBySlots; }

  void ShootBox(const Vector3f& cameraPosition, const Vector3f& direction);
 
  /**
   * This is called by Component instance to be processed in main loop
   */
  bool RegisterComponent(Component* pNewComponent);
  /**
   * Removes Component from main loop process
   */
  bool UnregisterComponent(Component* pComponent);



private:
  size_t MapTypeToSlot(size_t type);
  /** 
    * Adds pointer to this instance everywhere it needs to
    */
  bool AttachEntity(Entity* pEntity);
  /** 
    * Nulls pointer to this instance everywhere EnlistEntity added it
    */
  bool DetachEntity(Entity* pEntity);


  // Attributes
private:
  /** Owner ptr of SceneContext */
  std::unique_ptr<SceneContext> _pSceneContext;

  /** Pointer to owner Engine instance */
  Engine* _pEngine;

  /** Pointer to default Engine Editor camera instance */
  Camera* _pEditorCamera;

  /** Pointer to main Window instance that this Scene is being rendered to */
  Window* _pMainWindow;

  /** Pointer to PhysicsScene that corresponds to this Scene */
  PhysicsScene* _pPhysicsScene;

  /** Map of all child Entities */
  std::map<size_t, Entity*> _childEntities;
  
  /** 
  * Table of active primary Components on this Entity 
  *
  * Indices of slots are configured at config_components.h.
  * Some slots are singletons, e.g. there can be only one light source per Component.
  */
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> _activeComponentBySlots;

 
};

} // namespace SYE