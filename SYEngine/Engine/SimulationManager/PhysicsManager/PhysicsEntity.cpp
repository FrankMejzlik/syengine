#include "PhysicsEntity.h"

using namespace SYE;

PhysicsEntity::PhysicsEntity(
  size_t ownerEntityGuid, 
  std::unique_ptr<btCollisionShape>&& pCollisionShape,
  std::unique_ptr<btCollisionObject>&& _pPhysicsBody,
  std::unique_ptr<MotionState>&& _pMotionState
) noexcept:
  _pOwnerEntityGuid(ownerEntityGuid),
  _pCollisionShape(std::move(pCollisionShape)),
  _pPhysicsBody(std::move(_pPhysicsBody)),
  _pMotionState(std::move(_pMotionState))
{}