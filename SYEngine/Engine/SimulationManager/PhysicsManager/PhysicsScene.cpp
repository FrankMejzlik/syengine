#include "PhysicsScene.h"

#include "MotionState.h"
#include "Scene.h"
#include "Collider.h"
#include "PhysicsBody.h"
#include "Rigidbody.h"
#include "Softbody.h"
#include "BlockCollider.h"


using namespace SYE;

PhysicsScene::PhysicsScene(Scene* pOwnerScene) noexcept:
  _pOwnerScene(pOwnerScene)
{}


void PhysicsScene::Initialize()
{

  // Create the collision configuration
  _pCollisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
  // Create the dispatcher
  _pDispatcher = std::make_unique<btCollisionDispatcher>(_pCollisionConfiguration.get());
  // Create the broadphase
  _pBroadphaseInterface = std::make_unique<btDbvtBroadphase>();
  // Create the constraint solver
  _pSolver = std::make_unique<btSequentialImpulseConstraintSolver>();
  // Create the world
  _pWorld = std::make_unique<btDiscreteDynamicsWorld>(_pDispatcher.get(), _pBroadphaseInterface.get(), _pSolver.get(), _pCollisionConfiguration.get());

  // Create initial physics objects for Scene
  GenerateSceneObjects();
}

void PhysicsScene::ProcessScene(dfloat deltaTime)
{
  UNREFERENCED_PARAMETER(deltaTime);

  if (_pWorld)
  {
    _pWorld->stepSimulation(deltaTime);
  }

  //check collisions with player
  //m_dynamicsWorld->contactTest(mPlayerObject, resultCallback);
  auto disp = _pWorld->getDispatcher();
  int numManifolds = disp->getNumManifolds();
  for (int i = 0; i < numManifolds; i++)
  {
    btPersistentManifold* contactManifold = _pWorld->getDispatcher()->getManifoldByIndexInternal(i);
    const btCollisionObject* obA = contactManifold->getBody0(); obA;
    const btCollisionObject* obB = contactManifold->getBody1(); obB;

    Collider* obAPtr = static_cast<Collider*>(obA->getUserPointer()); obAPtr;
    Collider* obBPtr = static_cast<Collider*>(obB->getUserPointer()); obBPtr;

  #if LOG_PHYSICS_MANAGER_COLLISIONS
    DLog(eLogType::Info, "Collision between objects with IDs: %d, %d", obA->getUserIndex(), obB->getUserIndex());
  #endif
    int numContacts = contactManifold->getNumContacts();
    for (int j = 0; j<numContacts; j++)
    {
      btManifoldPoint& pt = contactManifold->getContactPoint(j);
      if (pt.getDistance()<0.f)
      {
        const btVector3& ptA = pt.getPositionWorldOnA(); ptA;



        const btVector3& ptB = pt.getPositionWorldOnB(); ptB;
        const btVector3& normalOnB = pt.m_normalWorldOnB; normalOnB;

      #if LOG_PHYSICS_MANAGER_COLLISIONS
        DLog(eLogType::Info, "contact %d:", j);
        DLog(eLogType::Info, "A pos: (%f, %f, %f)", ptA.getX(), ptA.getY(), ptA.getX());
        DLog(eLogType::Info, "B pos: (%f, %f, %f)", ptB.getX(), ptB.getY(), ptB.getZ());
        DLog(eLogType::Info, "B normal: (%f, %f, %f)", normalOnB.getX(), normalOnB.getY(), normalOnB.getZ());
      #endif
      }
    }
  }



  // Sync it
  SyncPhysicsToGraphics();
}

void PhysicsScene::SyncPhysicsToGraphics()
{
  int numCollisionObjects = _pWorld->getNumCollisionObjects();
  {

    for (int i = 0; i < numCollisionObjects; i++)
    {

      btCollisionObject* colObj = _pWorld->getCollisionObjectArray()[i];
      btCollisionShape* collisionShape = colObj->getCollisionShape(); collisionShape;


      btVector3 pos = colObj->getWorldTransform().getOrigin();
      btQuaternion orn = colObj->getWorldTransform().getRotation();

      btScalar rotX, rotY, rotZ;
      orn.getEulerZYX(rotX, rotY, rotZ);


      Collider* pCollider = static_cast<Collider*>(colObj->getUserPointer());

      // Set new values to object
      pCollider->SetTransformPosition(pos.getX(), pos.getY(), pos.getZ());
      pCollider->SetTransformRotation(rotX, rotY, rotZ);

    }
  }
}

void PhysicsScene::GenerateSceneObjects()
{
  // Get active PhysicsBodies - RigidBody, SoftBody
  auto physicsBodies = _pOwnerScene->GetActiveComponentsBySlotsRef()[COMPONENT_PHYSICS_BODY_SLOT];

  // Iteratre through all active PhysicsBodies
  for (auto&& bodyPair : physicsBodies)
  {
    Component* pBody = bodyPair.second;

    // Check if this Body is in scene already
    if (DoesContain(pBody->GetGuid()))
    {
      continue;
    }

    // Choose what type of PhysicsBody it is
    switch (pBody->GetType())
    {
      // RigidBody
      case static_cast<size_t>(Component::eType::RIGID_BODY) :
        AddRigidBody(static_cast<Rigidbody*>(pBody));
        break;

      // SoftBody
      case static_cast<size_t>(Component::eType::SOFT_BODY) :
        AddSoftBody(static_cast<Softbody*>(pBody));
        break;
    }
  }

}

bool PhysicsScene::DoesContain(size_t guid) const
{
  // Try to find this key
  const auto result = _entityToPhysicsEntitiyMap.find(guid);

  if (result == _entityToPhysicsEntitiyMap.end())
  {
    return false;
  }

  return true;
}

PhysicsEntity* PhysicsScene::AddRigidBody(Rigidbody* pBody)
{
  // Create collision mesh

  Collider* pCollider = pBody->GetCollider();

  // Choose what type of PhysicsBody it is
  switch (pCollider->GetType())
  {
    // BlockCollider
    case static_cast<size_t>(Component::eType::BLOCK_COLLIDER) :
      return AddBlockColliderRigidbody(pBody, pCollider);
      break;

    // SphereCollider
    case static_cast<size_t>(Component::eType::SPHERE_COLLIDER) :
      return AddSphereColliderRigidbody(pBody, pCollider);
      break;
  }

  return nullptr;
}

PhysicsEntity* PhysicsScene::AddSoftBody(Softbody* body)
{
  UNREFERENCED_PARAMETER(body);

  LOG_NOT_IMPLEMENTED;

  return nullptr;
}

PhysicsEntity* PhysicsScene::AddBlockColliderRigidbody(Rigidbody* pBody, Collider* pCollider)
{
  BlockCollider* pBlockCollider = static_cast<BlockCollider*>(pCollider);

  Vector3f dimensions = pBlockCollider->GetDimensions();
  Vector3f position = pBlockCollider->GetWorldPositionConstRef();
  Vector3f rotation = pBlockCollider->GetWorldRotationConstRef();
  Vector3f scale = pBlockCollider->GetWorldScaleConstRef();

  // Construct BT versions of those
  btVector3 btDimensions(dimensions.GetX() / 2, dimensions.GetY() / 2, dimensions.GetZ() / 2);
  btVector3 btPosition(position.GetX(), position.GetY(), position.GetZ());
  btVector3 btRotation(rotation.GetX(), rotation.GetY(), rotation.GetZ());
  btVector3 btScale(scale.GetX(), scale.GetY(), scale.GetZ());

  // Allocate new box shape
  std::unique_ptr<btCollisionShape> pBoxShape = std::make_unique<btBoxShape>(btDimensions);

  // Construct transform matrix
  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btPosition);
  transform.setRotation(btQuaternion(btRotation.x(), btRotation.y(), btRotation.z()));

  // Allocate new MotionState for this PhysicsEntity
  std::unique_ptr<MotionState> pMotionState = std::make_unique<MotionState>(transform);

  // Create Rigidbody info struct
  btRigidBody::btRigidBodyConstructionInfo rbInfo(pBody->GetMass(), pMotionState.get(), pBoxShape.get());

  // Instantiate new Rigidbody instance for this PhysicsEntity
  std::unique_ptr<btCollisionObject> pRigidBody = std::make_unique<btRigidBody>(rbInfo);

  // Setup user pointers for this Rigidbody
  pRigidBody->setUserIndex(static_cast<int>(pCollider->GetGuid()));
  pRigidBody->setUserPointer(pCollider);

  // If should be kinematic
  if (pBody->IsKinematic())
  {
    pRigidBody->setCollisionFlags(pRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    pRigidBody->setActivationState(DISABLE_DEACTIVATION);
    pRigidBody->activate(true);
  }
  

  // Add this Rigidbody into physics scene
  _pWorld->addRigidBody(static_cast<btRigidBody*>(pRigidBody.get()));

  // Instantiate new PhysicsEntity
  std::unique_ptr<PhysicsEntity> pPhysicsEntity = std::make_unique<PhysicsEntity>(
    pBody->GetOwnerEntityPtr()->GetGuid(), 
    std::move(pBoxShape), 
    std::move(pRigidBody), 
    std::move(pMotionState)
  );

  return InsertPhysicsEntity(std::move(pPhysicsEntity));
}

PhysicsEntity* PhysicsScene::AddSphereColliderRigidbody(Rigidbody* pBody, Collider* pCollider)
{
  UNREFERENCED_PARAMETER(pBody);
  UNREFERENCED_PARAMETER(pCollider);

  LOG_NOT_IMPLEMENTED;

  return nullptr;
}

PhysicsEntity* PhysicsScene::InsertPhysicsEntity(std::unique_ptr<PhysicsEntity>&& pEntity)
{
  auto result = _entityToPhysicsEntitiyMap.insert(std::make_pair(pEntity->GetOwnerEntityGuid(), std::move(pEntity)));

  return result.first->second.get();
}

bool PhysicsScene::RemovePhysicsEntity(PhysicsEntity* pEntity)
{
  if (pEntity == nullptr)
  {
    return false;
  }

  auto result = _entityToPhysicsEntitiyMap.erase(pEntity->GetOwnerEntityGuid());

  if (result < 1)
  {
    return false;
  }

  return true;
}