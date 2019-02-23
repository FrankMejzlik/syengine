#pragma once

#pragma warning (push, 0)
  #include "btBulletDynamicsCommon.h"
  #include "BulletDynamics/Dynamics/btDynamicsWorld.h"
  #include "BulletDynamics/ConstraintSolver/btConstraintSolver.h"
#pragma warning(pop)

#include "common.h"
#include "IGuidCounted.h"
#include "MotionState.h"

namespace SYE
{

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
    size_t ownerEntityGuid, 
    std::unique_ptr<btCollisionShape>&& pCollisionShape,
    std::unique_ptr<btCollisionObject>&& _pPhysicsBody,
    std::unique_ptr<MotionState>&& _pMotionState
  ) noexcept;

  size_t GetOwnerEntityGuid() const { return _pOwnerEntityGuid; }


  // Attributes
private:
  size_t _pOwnerEntityGuid;
  std::unique_ptr<btCollisionShape> _pCollisionShape;
  std::unique_ptr<btCollisionObject> _pPhysicsBody;
  std::unique_ptr<MotionState> _pMotionState;
};

};