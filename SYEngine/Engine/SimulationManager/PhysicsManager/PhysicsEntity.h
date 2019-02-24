#pragma once

#pragma warning (push, 0)
  #include "btBulletDynamicsCommon.h"
  #include "BulletDynamics/Dynamics/btDynamicsWorld.h"
  #include "BulletDynamics/ConstraintSolver/btConstraintSolver.h"
#pragma warning(pop)

#include "common.h"
#include "MathLibrary.h"
#include "IGuidCounted.h"
#include "MotionState.h"

namespace SYE
{

class Entity;
class Collider;
class PhysicsBody;

/**
 * Represents one instance of Physical Entity inside physics scene
 *
 * Must contain btCollisionObject or derivate of it. Also holds things like 
 * MotionStates.
 */
class PhysicsEntity:
  public IGuidCounted
{
  // Methods
public:
  PhysicsEntity() = delete;
  PhysicsEntity(
    Collider* pCollider, 
    PhysicsBody* pPhysicsBody,
    std::unique_ptr<btCollisionShape>&& pCollisionShape,
    dfloat mass,
    const Vector3f& color
  ) noexcept;

  size_t GetOwnerEntityGuid() const;
  void SetLocalInertia(const Vector3f& localInertia);

  btCollisionObject* GetCollisionObjectPtr() const;

  // Attributes
private:
  Entity* _pOwnerEntity;
  Collider* _pCollider;
  PhysicsBody* _pPhysicsBody;

  std::unique_ptr<btCollisionObject> _pCollisionObject; // Handle to dynamic world
  std::unique_ptr<btCollisionShape> _pCollisionShape;
  std::unique_ptr<MotionState> _pMotionState;

  dfloat _mass;
  Vector3f _color;
  Vector3f _localInertia;

  btVector3 _position;
  btQuaternion _rotation;

  


};

};