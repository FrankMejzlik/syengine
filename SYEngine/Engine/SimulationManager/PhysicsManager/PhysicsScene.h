#pragma once

#include <memory>
#include <map>

#pragma warning (push, 0)
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/ConstraintSolver/btConstraintSolver.h"
#pragma warning(pop)

#include "common.h"
#include "PhysicsEntity.h"

namespace SYE
{

// Forward declarations
class PhysicsEntity;
class Scene;
class Collider;
class PhysicsBody;
class Rigidbody;
class Softbody;

/**
 * Implementation of engine processing all physics
 *
 * Currently implementing Bullet3 physics engine.
 *    https://github.com/bulletphysics/bullet3
 */
class PhysicsScene
{
public:
  PhysicsScene() = delete;
  PhysicsScene(Scene* pOwnerScene) noexcept;

  void Initialize();
  void ProcessScene(dfloat deltaTime);


private:
  void GenerateSceneObjects();
  bool DoesContain(size_t guid) const;

  PhysicsEntity* AddRigidBody(Rigidbody* pBody);
  PhysicsEntity* AddSoftBody(Softbody* body);

  PhysicsEntity* AddBlockColliderRigidbody(Rigidbody* pBody, Collider* pCollider);
  PhysicsEntity* AddSphereColliderRigidbody(Rigidbody* pBody, Collider* pCollider);

  void SyncPhysicsToGraphics();

  PhysicsEntity* InsertPhysicsEntity(std::unique_ptr<PhysicsEntity>&& pEntity);
  bool RemovePhysicsEntity(PhysicsEntity* pEntity);

private:
  /** Scene that this physics scene belongs to */
  Scene* _pOwnerScene;

  /** Mapping Entity GUID to existing PhysicsEntities */
  std::map< size_t, std::unique_ptr<PhysicsEntity> > _entityToPhysicsEntitiyMap;

  /** Clock for time tracking purposes */
  btClock _clock;

  /** How broadphase is solved */
  std::unique_ptr<btBroadphaseInterface> _pBroadphaseInterface;

  /** Configuration for collision detection */
  std::unique_ptr<btCollisionConfiguration> _pCollisionConfiguration;

  /** Collision dispatcher for this world */
  std::unique_ptr<btCollisionDispatcher> _pDispatcher;

  /** Solver for our world */
  std::unique_ptr<btConstraintSolver> _pSolver;

  /** Dynamic physics world */
  std::unique_ptr<btDynamicsWorld> _pWorld;

};

};