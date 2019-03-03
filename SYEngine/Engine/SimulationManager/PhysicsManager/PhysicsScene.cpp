#include "PhysicsScene.h"

#include "MotionState.h"
#include "Scene.h"
#include "Collider.h"
#include "PhysicsBody.h"
#include "Rigidbody.h"
#include "Softbody.h"
#include "BlockCollider.h"
#include "SphereCollider.h"
#include "PhysicsDebugRenderer.h"
#include "PhysicsBody.h"
#include "Transform.h"
#include "ConvexHullCollider.h"
#include "BallController.h"

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

  // Set gravity
  _pWorld->setGravity(btVector3(0.0f, -9.80665f, 0.0f));

  // Create initial physics objects for Scene
  //InsertInitialPhysicsEntities();
}

void PhysicsScene::ProcessScene(dfloat deltaTime)
{
  UNREFERENCED_PARAMETER(deltaTime);

  if (_pWorld)
  {
    _pWorld->stepSimulation(deltaTime, 10, 1/120.0f);
  }

  // Check collisions
  auto disp = _pWorld->getDispatcher();
  int numManifolds = disp->getNumManifolds();

  for (int i = 0; i < numManifolds; i++)
  {
    btPersistentManifold* contactManifold = _pWorld->getDispatcher()->getManifoldByIndexInternal(i);
    
    const btCollisionObject* obA = contactManifold->getBody0(); obA;
    const btCollisionObject* obB = contactManifold->getBody1(); obB;

    // Get pointers to PhysicsBodies
    PhysicsBody* obAPtr = static_cast<PhysicsBody*>(obA->getUserPointer()); obAPtr;
    PhysicsBody* obBPtr = static_cast<PhysicsBody*>(obB->getUserPointer()); obBPtr;


    // TODO: This should be in scripted part of game outside of engine

    // If Ball + Hitter collision
    // Sum of 3 means that it is ball + hitter pair
    if (obAPtr->GetTag() + obBPtr->GetTag() == 3ULL)
    {
      // Get num contacts
      int numContacts = contactManifold->getNumContacts();
      for (int j = 0; j < numContacts; j++)
      {
        btManifoldPoint& pt = contactManifold->getContactPoint(j);
        if (pt.getDistance() < 0.f)
        {
          PhysicsBody* pBall;

          // Decde what is Ball object
          if (obAPtr->GetTag() == 1ULL)
          {
            pBall = obAPtr;
          }
          else
          {
            pBall = obBPtr;
          }

          //const btVector3& ptA = pt.getPositionWorldOnA(); ptA;
          //const btVector3& ptB = pt.getPositionWorldOnB(); ptB;
          //const btVector3& normalOnB = pt.m_normalWorldOnB; normalOnB;

          // Tick on BallController script
          BallController* pScript = static_cast<BallController*>(pBall->GetFirstScriptHandlerPtr()->GetAttachedScriptPtr());
          pScript->TickScore();

        }
      }
    }
  }

  // Draw debug physics info
  //_pWorld->debugDrawWorld();

  // Sync it
  SyncPhysicsToGraphics();
}

void PhysicsScene::DrawDebug(GLuint shaderId, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
  _pDebugRenderer->SetMatrices(shaderId, viewMatrix, projectionMatrix);

  _pWorld->debugDrawWorld();
}

void PhysicsScene::SetDebugRenderer(PhysicsDebugRenderer* pDebugRenderer)
{
  // Store it for later
  _pDebugRenderer = pDebugRenderer;

  btIDebugDraw* ptr = (btIDebugDraw*)(_pDebugRenderer);

  assert(_pWorld != nullptr); // Setting debug renderer before physics scene was initialized

  _pWorld->setDebugDrawer(ptr);
  
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
      orn.getEulerZYX(rotZ, rotY, rotX);


      void* ptr = colObj->getUserPointer();
      PhysicsBody* pPhysBody = (PhysicsBody*)(ptr);

      if (pPhysBody)
      {

        // Sync only non kinematic objects
        if (!pPhysBody->IsKinematic())
        {
          pPhysBody->GetTransformPtr()->SetPosition(pos);
          pPhysBody->GetTransformPtr()->SetRotation(Vector3f(rotX, rotY, rotZ));
        }
      }

    }
  }
}

void PhysicsScene::InsertInitialPhysicsEntities()
{
  // Get active PhysicsBodies - RigidBody, SoftBody
  auto physicsBodies = _pOwnerScene->GetActivePrimaryComponentSlotsRef()[COMPONENT_PHYSICS_BODY_SLOT];

  // Iteratre through all active PhysicsBodies
  for (auto&& bodyPair : physicsBodies)
  {
    Component* pBody = bodyPair.second;

    // Check if this Body is in scene already
    if (DoesContain(pBody->GetGuid()))
    {
      continue;
    }
    InsertPhysicsEntity(static_cast<PhysicsBody*>(pBody));
  }

}

bool PhysicsScene::RemovePhysicsEntity(PhysicsBody* pBody)
{
  auto result = _entityToPhysicsEntitiyMap.erase(pBody->GetOwnerEntityPtr()->GetGuid());

  if (result <= 0)
  {
    return false;
  }

  return true;
}

PhysicsEntity* PhysicsScene::InsertPhysicsEntity(PhysicsBody* pBody)
{
  PhysicsEntity* pNewPhysEntity(nullptr);

  // Choose what type of PhysicsBody it is
  switch (pBody->GetType())
  {
    // RigidBody
    case static_cast<size_t>(Component::eType::RIGID_BODY) :
      pNewPhysEntity = AddRigidBody(static_cast<Rigidbody*>(pBody));
      break;

    // SoftBody
    case static_cast<size_t>(Component::eType::SOFT_BODY) :
      pNewPhysEntity = AddSoftBody(static_cast<Softbody*>(pBody));
      break;

  }

  // Set this PhysEntity to PhysicsBody Component
  static_cast<PhysicsBody*>(pBody)->SetPhysicsEntity(pNewPhysEntity);

  return pNewPhysEntity;
}

void PhysicsScene::RemoveFromPhysicsScene(PhysicsEntity* pPhysEntity)
{
  _pWorld->removeCollisionObject(pPhysEntity->GetCollisionObjectPtr());
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

    // ConvexHullCollider
    case static_cast<size_t>(Component::eType::CONVEX_HULL_COLLIDER) :
      return AddConvexHullColliderRigidbody(pBody, pCollider);
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

std::pair<PhysicsBody*, Vector3f> PhysicsScene::Raycast(const Vector3f& from, const Vector3f& direction)
{
  // If world not set
  if (!_pWorld)
  {
    PUSH_ENGINE_ERROR(eEngineError::PhysicsWorldNotSet, "Physics world not set.", "");

    return std::make_pair(nullptr, Vector3f(0.0f, 0.0f, 0.0f));
  }

  // Get the picking ray
  btVector3 rayTo = direction;
  btVector3 rayFrom = from;

  // Create our raycast callback object
  btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);

  // Perform the raycast
  _pWorld->rayTest(rayFrom, rayTo, rayCallback);

  // If we hit something
  if (rayCallback.hasHit())
  {
    // Upcast result to rigidbody
    //const btRigidBody* pBody = btRigidBody::upcast(rayCallback.m_collisionObject);
    const btCollisionObject* pBody = rayCallback.m_collisionObject;
    // If not valid ptr
    if (!pBody)
    {
      PUSH_ENGINE_ERROR(eEngineError::PhysicsLibRaycastWeirdResult, "There should be hit, but no pointer to object.", "");

      return std::make_pair(nullptr, Vector3f(0.0f, 0.0f, 0.0f));
    }

    // Get corresponding PhysicsBody instance ptr
    PhysicsBody* pPhysBody = static_cast<PhysicsBody*>(pBody->getUserPointer());
    Vector3f hitPoint(rayCallback.m_hitPointWorld);
    
    return std::make_pair(pPhysBody, hitPoint);
  }

  // No hit
  return std::make_pair(nullptr, Vector3f(0.0f, 0.0f, 0.0f));
}

PhysicsEntity* PhysicsScene::AddBlockColliderRigidbody(Rigidbody* pBody, Collider* pCollider)
{
  BlockCollider* pBlockCollider = static_cast<BlockCollider*>(pCollider);

  // Get Collider dimensions and scale
  Vector3f dimensions = pBlockCollider->GetDimensions();
  Vector3f scale = pBlockCollider->GetWorldScaleConstRef();

  // Construct BT versions of those
  btVector3 btDimensions(dimensions.GetX() / 2, dimensions.GetY() / 2, dimensions.GetZ() / 2);
  btVector3 btScale(scale.GetX(), scale.GetY(), scale.GetZ());

  // Allocate new box shape
  std::unique_ptr<btCollisionShape> pBoxShape = std::make_unique<btBoxShape>(btDimensions);
  // Scale it propperly
  pBoxShape->setLocalScaling(btScale);

  // Instantiate new PhysicsEntity
  std::unique_ptr<PhysicsEntity> pPhysicsEntity = std::make_unique<PhysicsEntity>(
    this,
    pCollider,
    pBody,
    std::move(pBoxShape),
    pBody->GetMass(),
    Vector3f(0.0f, 1.0f, 0.0)
  );

  // Activate this PO inside physics scene
  _pWorld->addRigidBody(static_cast<btRigidBody*>(pPhysicsEntity->GetCollisionObjectPtr()));

  return InsertPhysicsEntity(std::move(pPhysicsEntity));
}



PhysicsEntity* PhysicsScene::AddSphereColliderRigidbody(Rigidbody* pBody, Collider* pCollider)
{
  SphereCollider* pSphereCollider = static_cast<SphereCollider*>(pCollider);

  // Get Collider dimensions and scale
  dfloat radius = pSphereCollider->GetRadius();
  Vector3f scale = pSphereCollider->GetWorldScaleConstRef();

  // Construct BT versions of those
  btVector3 btScale(scale.GetX(), scale.GetY(), scale.GetZ());

  // Allocate new box shape
  std::unique_ptr<btCollisionShape> pSphereShape = std::make_unique<btSphereShape>(radius);
  // Scale it propperly
  pSphereShape->setLocalScaling(btScale);

  // Instantiate new PhysicsEntity
  std::unique_ptr<PhysicsEntity> pPhysicsEntity = std::make_unique<PhysicsEntity>(
    this,
    pCollider,
    pBody,
    std::move(pSphereShape),
    pBody->GetMass(),
    Vector3f(0.0f, 1.0f, 0.0)
    );

  // Activate this PO inside physics scene
  _pWorld->addRigidBody(static_cast<btRigidBody*>(pPhysicsEntity->GetCollisionObjectPtr()));

  return InsertPhysicsEntity(std::move(pPhysicsEntity));
  return nullptr;
}

PhysicsEntity* PhysicsScene::AddConvexHullColliderRigidbody(Rigidbody* pBody, Collider* pCollider)
{
  ConvexHullCollider* pConvHullCollider = static_cast<ConvexHullCollider*>(pCollider);

  // Get Collider dimensions and scale
  const std::vector<Vector3f>& vertices = pConvHullCollider->GetVerticesConstRef();
  Vector3f scale = pConvHullCollider->GetWorldScaleConstRef();

  std::vector<dfloat> verticesData;
  verticesData.reserve(vertices.size() * 3);

  // Create correct format vector
  for (auto&& v : vertices)
  {
    verticesData.push_back(v.GetX());
    verticesData.push_back(v.GetY());
    verticesData.push_back(v.GetZ());
  }

  // Construct BT versions of those
  btVector3 btScale(scale.GetX(), scale.GetY(), scale.GetZ());

  // Allocate new box shape
  //btConvexHullShape(const btScalar* points = 0, int numPoints = 0, int stride = sizeof(btVector3));
  std::unique_ptr<btCollisionShape> pSphereShape = std::make_unique<btConvexHullShape>(verticesData.data(), static_cast<int>(vertices.size()), static_cast<int>(3 *sizeof(dfloat)));
  
  // Scale it propperly
  pSphereShape->setLocalScaling(btScale);

  // Instantiate new PhysicsEntity
  std::unique_ptr<PhysicsEntity> pPhysicsEntity = std::make_unique<PhysicsEntity>(
    this,
    pCollider,
    pBody,
    std::move(pSphereShape),
    pBody->GetMass(),
    Vector3f(0.0f, 1.0f, 0.0)
    );

  // Activate this PO inside physics scene
  _pWorld->addRigidBody(static_cast<btRigidBody*>(pPhysicsEntity->GetCollisionObjectPtr()));

  return InsertPhysicsEntity(std::move(pPhysicsEntity));
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