#pragma once

#include "BaseModule.h"

#include "Scene.h"

// Include Bullet3 headers.
#pragma warning (push, 0)
  #include "btBulletDynamicsCommon.h"
  #include "btBulletCollisionCommon.h"

  #include "LinearMath/btVector3.h"
  #include "LinearMath/btAlignedObjectArray.h"

  #include "bullet3parts/CommonRigidBodyBase.h"
#pragma warning(pop)


using namespace SYE;

namespace SYE {


class Bullet3Wrapper:
  public CommonRigidBodyBase
{
public:
  Bullet3Wrapper(struct GUIHelperInterface* helper): 
    CommonRigidBodyBase(helper)
  {}
  virtual ~Bullet3Wrapper() {}

  

public:


  static bool EntityCollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
  {
    index1; 
    colObj1Wrap;
    index0;
    colObj0Wrap;
    cp;

    DLog(eLogType::Info, "collision on objs %d, %d", partId0, partId1);
    return true;
  }

  void SetScene(Scene* pScene)
  {
    _pScene = pScene;
  }
  Scene* _pScene;

  

  virtual void initPhysics()
  {
    // Get active Colliders in Scene
    auto colliders = _pScene->GetActiveComponentsBySlotsRef()[COMPONENT_PHYSICS_COLLIDER_SLOT];

    // Create Physics world
    createEmptyDynamicsWorld();

    // Initialize all Colliders
    for (auto&& colliderPair : colliders)
    {
      // Cast it to Collider
      Collider* pCollider = static_cast<Collider*>(colliderPair.second);

      // Get pos, rot and scale
      Vector3f position = pCollider->GetWorldPositionConstRef();
      Vector3f rotation = pCollider->GetWorldRotationConstRef();
      Vector3f scale = pCollider->GetWorldScaleConstRef();

      // Construct BT versions of those
      btVector3 btPosition(position.GetX(), position.GetY(), position.GetZ());
      btVector3 btRotation(rotation.GetX(), rotation.GetY(), rotation.GetZ());
      btVector3 btScale(scale.GetX(), scale.GetY(), scale.GetZ());

      // Get vertices and indices to construct collision mesh
      std::vector<dfloat> vertices = pCollider->GetVertices();
      std::vector<unsigned int> indices = pCollider->GetIndices();

      size_t numIndices = indices.size();

      // Instantiate triangle BT Mesh
      btTriangleMesh* btCollisionMesh = new btTriangleMesh();

    #if LOG_PHYSICS_MANAGER_COLLISION_MESH_CONSTRUCTION
      DLog(eLogType::Info, "Constructing mesh for Bullet3:");
    #endif

      for (int i = 0; i < numIndices; i = i + 3)
      {
      #if LOG_PHYSICS_MANAGER_COLLISION_MESH_CONSTRUCTION
        DLog(eLogType::Info, "triangle %d:", i / 3);
        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i] * 8], vertices[indices[i] * 8 + 1], vertices[indices[i] * 8 + 2]);
        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i + 1] * 8], vertices[indices[i + 1] * 8 + 1], vertices[indices[i + 1] * 8 + 2]);
        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i + 2] * 8], vertices[indices[i + 2] * 8 + 1], vertices[indices[i + 2] * 8 + 2]);
      #endif

        // Set correct staling for this mesh
        btCollisionMesh->setScaling(btScale);

        // Add all trianges of this mesh
        btCollisionMesh->addTriangle(
          btVector3(
            vertices[indices[i] * 8], 
            vertices[indices[i] * 8 + 1], 
            vertices[indices[i] * 8 + 2]
          ),
          btVector3(
            vertices[indices[i + 1] * 8],
            vertices[indices[i + 1] * 8 + 1],
            vertices[indices[i + 1] * 8 + 2]
          ),
          btVector3(
            vertices[indices[i + 2] * 8],
            vertices[indices[i + 2] * 8 + 1],
            vertices[indices[i + 2] * 8 + 2]
          ),
          true
        );
      }

    #if LOG_PHYSICS_MANAGER_COLLISION_MESH_CONSTRUCTION
      DLog(eLogType::Info, "------------------------");
    #endif

      // Create convex triangle collision mesh from this
      btConvexShape* pCollisionTriMesh = new btConvexTriangleMeshShape(btCollisionMesh);

      // Add it into collision shapes
      m_collisionShapes.push_back(pCollisionTriMesh);

      /**
       * Create rigidbody
       */

      // Create transform matrix
      btTransform btTransform;
      // Initialize it as identity
      btTransform.setIdentity();
      // Set position
      btTransform.setOrigin(btPosition);
      // Set rotation
      btTransform.setRotation(btQuaternion(btRotation.x(), btRotation.y(), btRotation.z()));
      
      // Set mass
      btScalar mass = 1.0f;
      

      auto newRb = createRigidBody(mass, btTransform, pCollisionTriMesh, btVector4(0, 0, 1, 1));
      newRb->setGravity(btVector3(0.0f, 0.0f, 0.0f));
      newRb->setUserIndex(static_cast<int>(pCollider->GetGuid()));
      newRb->setUserPointer(pCollider);
    }

  }

  virtual void stepSimulation(float deltaTime)
  {
    UNREFERENCED_PARAMETER(deltaTime);

    if (m_dynamicsWorld)
    {
      m_dynamicsWorld->stepSimulation(deltaTime);
    }

    //check collisions with player
    //m_dynamicsWorld->contactTest(mPlayerObject, resultCallback);
    int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();
    for (int i = 0; i < numManifolds; i++)
    {
      btPersistentManifold* contactManifold = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
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

  }

  void syncPhysicsToGraphics()
  {
    auto rbWorld = m_dynamicsWorld;
    int numCollisionObjects = rbWorld->getNumCollisionObjects();
    {
      
      for (int i = 0; i < numCollisionObjects; i++)
      {

        btCollisionObject* colObj = rbWorld->getCollisionObjectArray()[i];
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
};


class PhysicsManager :
  public BaseModule
{
public:
  PhysicsManager() = delete;

  PhysicsManager(BaseModule &parentModule);
  ~PhysicsManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void InitializePhysicsScene(Scene* pScene);

  void ProcessScene(dfloat deltaTime, Scene* pScene);


private:
  Bullet3Wrapper _bulletPhysics;
};

}