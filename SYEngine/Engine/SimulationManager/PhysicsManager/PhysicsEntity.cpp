
#include "PhysicsEntity.h"

#include "Entity.h"
#include "Collider.h"
#include "PhysicsBody.h"

using namespace SYE;

PhysicsEntity::PhysicsEntity(
  Collider* pCollider, 
  PhysicsBody* pPhysicsBody,
  std::unique_ptr<btCollisionShape>&& pCollisionShape,
  dfloat mass,
  const Vector3f& color
) noexcept :
  _pOwnerEntity(pPhysicsBody->GetOwnerEntityPtr()),
  _pCollider(pCollider),
  _pPhysicsBody(pPhysicsBody),
  _pCollisionShape(std::move(pCollisionShape)),
  _mass(mass),
  _color(color),
  _localInertia(Vector3f(0.0f, 0.0f, 0.0))
{
  Vector3f position = _pCollider->GetWorldPositionConstRef();
  Vector3f rotation = _pCollider->GetWorldRotationConstRef();
  
  btVector3 btPosition(position.GetX(), position.GetY(), position.GetZ());
  btVector3 btRotation(rotation.GetX(), rotation.GetY(), rotation.GetZ());

  // Construct transform matrix
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btPosition);
  transform.setRotation(btQuaternion(btRotation.x(), btRotation.y(), btRotation.z()));

  // Allocate new MotionState for this PhysicsEntity
  _pMotionState = std::make_unique<MotionState>(transform);

  // If non-zero mass calculate local inertia
  if (mass > 0.0f)
  {
    btVector3 btLocalInertia;
    _pCollisionShape->calculateLocalInertia(mass, btLocalInertia);
    _localInertia = btLocalInertia;
  }

  // Create Rigidbody info struct
  btRigidBody::btRigidBodyConstructionInfo rbInfo(
    _mass, _pMotionState.get(), 
    _pCollisionShape.get(), 
    _localInertia);

  // Instantiate new Rigidbody instance for this PhysicsEntity
  _pCollisionObject = std::make_unique<btRigidBody>(rbInfo);

  _pCollisionObject->setRestitution(_pPhysicsBody->GetRestitution());


  // Setup user index #1 to correspond to PhysicsBody instance
  _pCollisionObject->setUserIndex(static_cast<int>(pPhysicsBody->GetGuid()));
  // Setup user index #2 to correspond to Entity that owns this PhysicsBody
  _pCollisionObject->setUserIndex2(static_cast<int>(_pOwnerEntity->GetGuid()));
  // Setup user pointer to correctponding PhysicsBody
  _pCollisionObject->setUserPointer(pPhysicsBody);

  // If should be kinematic
  if (_pPhysicsBody->IsKinematic())
  {
    _pCollisionObject->setCollisionFlags(_pCollisionObject->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    _pCollisionObject->setActivationState(DISABLE_DEACTIVATION);
  }

}

void PhysicsEntity::SetRestitution(dfloat newValeue)
{
  _pCollisionObject->setRestitution(newValeue);
}

dfloat PhysicsEntity::GetRestitution() const
{
  return _pCollisionObject->getRestitution();
}

size_t PhysicsEntity::GetOwnerEntityGuid() const
{
  return _pOwnerEntity->GetGuid();
}


btCollisionObject* PhysicsEntity::GetCollisionObjectPtr() const
{
  return _pCollisionObject.get();
}

void PhysicsEntity::SetLocalInertia(const Vector3f& localInertia)
{
  _localInertia = localInertia;

  // Set it to RB inside physics library
  LOG_NOT_IMPLEMENTED;
}