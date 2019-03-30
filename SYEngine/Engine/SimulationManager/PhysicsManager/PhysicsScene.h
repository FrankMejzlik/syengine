#pragma once

#include <memory>
#include <map>

#pragma warning (push, 0)
#include "btBulletDynamicsCommon.h"
#pragma warning(pop)

#include "common.h"
#include "MathLibrary.h"
#include "IErrorLogging.h"

namespace SYE
{

// Forward declarations
class PhysicsEntity;
class Scene;
class Collider;
class PhysicsBody;
class Rigidbody;
class Softbody;
class PhysicsDebugRenderer;

/*!
 * Class responsible for representation of physical scene.
 * 
 * Currently implementing Bullet3 physics engine.
 *    https://github.com/bulletphysics/bullet3
 */
class PhysicsScene :
  public IErrorLogging
{
  // Methods
public:
  PhysicsScene() = delete;
  /*!
   * Only possible constructor
   * 
   * \param pOwnerScene Pointer to Scene we're attached to.
   */
  PhysicsScene(Scene* pOwnerScene) noexcept;

  /*!
   * Initializes physics scene
   * 
   * It creates all instances that physics engine needs to simulate world and
   * also configures our physical world (e.g. sets gravity acceleration).
   */
  void Initialize();

  /*!
   * Processes physics for this discrete moment in time for provided delta time
   * 
   * \param deltaTime Time since last simulation.
   */
  void ProcessScene(dfloat deltaTime);

  /*!
   * Draws debug geometries into scene with provided Shader and matrices.
   * 
   * \param shaderId  Handle to Shader that will be used.
   * \param viewMatrix  Camera view matrix.
   * \param projectionMatrix  Camera projection matrix.
   */
  void DrawDebug(size_t shaderId, const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix);

  /*!
   * Casts ray from provided point in world to specified direction and 
   * returns PhysicsBody it hits first and point where it intersects.
   * 
   * \param from  Point from we're casting ray.
   * \param direction Direction of ray.
   * \return  Pair with pointer to PhysicsBody hit and world point of intersection.
   */
  std::pair<PhysicsBody*, Vector3f> Raycast(const Vector3f& from, const Vector3f& direction);

  /*!
   * Sets renderer for physics debug rendering.
   * 
   * \param pDebugRenderer  Pointer to new debug renderer.
   */
  void SetDebugRenderer(PhysicsDebugRenderer* pDebugRenderer);

  /*!
   * Inserts provided PhysicsBody into PhysicsScene
   * 
   * \param pBody PhysicsBody to insert.
   * \return  Pointer to PhysicsEntity that represents provided body.
   */
  PhysicsEntity* InsertPhysicsEntity(PhysicsBody* pBody);

  /*!
   * Removes PhysicsEntity from physical scene
   * 
   * \param pBody Pointer to PhysicsBody to remove.
   * \return  True if body was removed. 
   *          False if nothing was removed.
   */
  bool RemovePhysicsEntity(PhysicsBody* pBody);

  /*!
   * Removed provided PhysicsEntity from implemented physics engine world.
   * 
   * \note This is called from destructor of PhysicsEntitiy so no valid pointers remain after their destruction.
   * 
   * \param pPhysEntity Pointer to PhysicsEntity to remove.
   */
  void RemoveFromPhysicsScene(PhysicsEntity* pPhysEntity);


private:  
  /*!
   * Processes current collisions in attached physics world
   */
  void ProcessCollisions() const;
  
  /*!
   * Adds provided Rigidbody to PhysicsScene
   * 
   * \param pBody Body to add.
   * \return Pointer to PhysicsEntity representing this body.
   */
  PhysicsEntity* AddRigidBody(Rigidbody* pBody);

  /*!
   * Adds provided Softbody to PhysicsScene
   * 
   * \param pBody Body to add.
   * \return Pointer to PhysicsEntity representing this body.
   */
  PhysicsEntity* AddSoftBody(Softbody* body);

  /*!
   * Adds Rigidbody with block collision geometry
   * 
   * \param pBody Rigidbody to add.
   * \param pCollider Collider representing collision geometry.
   * \return Pointer to added PhysicsEntity.
   */
  PhysicsEntity* AddBlockColliderRigidbody(Rigidbody* pBody, Collider* pCollider);

  /*!
   * Adds Rigidbody with sphere collision geometry
   * 
   * \param pBody Rigidbody to add.
   * \param pCollider Collider representing collision geometry.
   * \return Pointer to added PhysicsEntity.
   */
  PhysicsEntity* AddSphereColliderRigidbody(Rigidbody* pBody, Collider* pCollider);

  /*!
   * Adds Rigidbody with convex hull collision geometry
   * 
   * \param pBody Rigidbody to add.
   * \param pCollider Collider representing collision geometry.
   * \return Pointer to added PhysicsEntity.
   */
  PhysicsEntity* AddConvexHullColliderRigidbody(Rigidbody* pBody, Collider* pCollider);

  /*!
   * Synchronizes changes from PhysicsScene to Scene
   */
  void SyncPhysicsToGraphics();

  /*!
   * Inserts owner pointer to list of PhysicsEntities
   * 
   * \param pEntity Owner pointer to new PhysicsEntity.
   * \return  Observer pointer to newly inserted PhysicsEntity.
   */
  PhysicsEntity* InsertPhysicsEntity(std::unique_ptr<PhysicsEntity>&& pEntity);

  /*!
   * Removes owner pointer to list of PhysicsEntities so it is destructed
   * 
   * \param pEntity Pointer to PhysicsEntity we want to destruct
   * \return  True if some PhysicsEntity was actually destructed. 
   *          False if no such PhysicsEntity found.
   */
  bool RemovePhysicsEntity(PhysicsEntity* pEntity);


  // Attributes
private:
  //! Scene that this physics scene belongs to
  Scene* _pOwnerScene;
  
  //! Debug renderer for physics
  PhysicsDebugRenderer* _pDebugRenderer;

  //!  How broadphase is solved
  std::unique_ptr<btBroadphaseInterface> _pBroadphaseInterface;

  //!  Configuration for collision detection
  std::unique_ptr<btCollisionConfiguration> _pCollisionConfiguration;

  //!  Collision dispatcher for this world
  std::unique_ptr<btCollisionDispatcher> _pDispatcher;

  //!  Solver for our world
  std::unique_ptr<btConstraintSolver> _pSolver;

  //!  Dynamic physics world
  std::unique_ptr<btDynamicsWorld> _pWorld;

  //!  Mapping Entity GUID to existing PhysicsEntities
  std::map< size_t, std::unique_ptr<PhysicsEntity> > _entityToPhysicsEntitiyMap;
};

};
