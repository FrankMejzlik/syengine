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
  {
  }
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

//    auto colliders = _pScene->GetActiveColliders();
//
//    createEmptyDynamicsWorld();
//
//    for (auto && it : colliders)
//    {
//
//      Collider* collider = it.second;
//
//      std::vector<GLfloat> vertices = collider->GetVertices();
//      std::vector<unsigned int> indices = collider->GetIndices();
//
//      size_t count = indices.size();
//
//      btTriangleMesh* mesh = new btTriangleMesh();
//
//#if LOG_PHYSICS_MANAGER_COLLISION_MESH_CONSTRUCTION
//
//      DLog(eLogType::Info, "Constructing mesh for Bullet3");
//#endif
//      for (int i = 0; i < count; i = i + 3)
//      {
//#if LOG_PHYSICS_MANAGER_COLLISION_MESH_CONSTRUCTION
//        DLog(eLogType::Info, "triangle %d:", i / 3);
//        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i] * 8], vertices[indices[i] * 8 + 1], vertices[indices[i] * 8 + 2]);
//        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i + 1] * 8], vertices[indices[i + 1] * 8 + 1], vertices[indices[i + 1] * 8 + 2]);
//        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i + 2] * 8], vertices[indices[i + 2] * 8 + 1], vertices[indices[i + 2] * 8 + 2]);
//#endif
//
//        mesh->addTriangle(
//          btVector3(
//            vertices[indices[i] * 8], 
//            vertices[indices[i] * 8 + 1], 
//            vertices[indices[i] * 8 + 2]
//          ),
//          btVector3(
//            vertices[indices[i + 1] * 8],
//            vertices[indices[i + 1] * 8 + 1],
//            vertices[indices[i + 1] * 8 + 2]
//          ),
//          btVector3(
//            vertices[indices[i + 2] * 8],
//            vertices[indices[i + 2] * 8 + 1],
//            vertices[indices[i + 2] * 8 + 2]
//          ),
//          true
//        );
//      }
//
//#if LOG_PHYSICS_MANAGER_COLLISION_MESH_CONSTRUCTION
//      DLog(eLogType::Info, "------------------------");
//#endif
//
//      //btBvhTriangleMeshShape* trimesh = new btBvhTriangleMeshShape(mesh, true, true);
//      btConvexShape* trimesh = new btConvexTriangleMeshShape(mesh);
//      m_collisionShapes.push_back(trimesh);
//
//      // Create rigidbody
//      btTransform transform;
//      transform.setIdentity();
//      transform.setOrigin(
//        btVector3(
//          collider->GetAbsolutePositionConstRef().x, 
//          collider->GetAbsolutePositionConstRef().y,
//          collider->GetAbsolutePositionConstRef().z
//        )
//      );
//      transform.setRotation(
//        btQuaternion(
//          collider->GetAbsoluteRotationConstRef().x,
//          collider->GetAbsoluteRotationConstRef().y,
//          collider->GetAbsoluteRotationConstRef().z
//        )
//      );
//      
//
//      btScalar mass = 0.0f;
//      if (!collider->GetBIsStatic())
//      {
//        mass = 1.0f;
//      }
//
//      
//      auto newRb = createRigidBody(mass, transform, trimesh, btVector4(0, 0, 1, 1));
//      newRb->setUserIndex(static_cast<int>(collider->GetGuid()));
//      newRb->setUserPointer(collider);
//    }

  }

  virtual void stepSimulation(float deltaTime)
  {
    UNREFERENCED_PARAMETER(deltaTime);

//    if (m_dynamicsWorld)
//    {
//      m_dynamicsWorld->stepSimulation(deltaTime);
//    }
//
//    //check collisions with player
//    //m_dynamicsWorld->contactTest(mPlayerObject, resultCallback);
//    int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();
//    for (int i = 0; i < numManifolds; i++)
//    {
//      btPersistentManifold* contactManifold = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
//      const btCollisionObject* obA = contactManifold->getBody0(); obA;
//      const btCollisionObject* obB = contactManifold->getBody1(); obB;
//
//      Collider* obAPtr = static_cast<Collider*>(obA->getUserPointer()); obAPtr;
//      Collider* obBPtr = static_cast<Collider*>(obB->getUserPointer()); obBPtr;
//
//#if LOG_PHYSICS_MANAGER_COLLISIONS
//      DLog(eLogType::Info, "Collision between objects with IDs: %d, %d", obA->getUserIndex(), obB->getUserIndex());
//#endif
//      int numContacts = contactManifold->getNumContacts();
//      for (int j = 0; j<numContacts; j++)
//      {
//        btManifoldPoint& pt = contactManifold->getContactPoint(j);
//        if (pt.getDistance()<0.f)
//        {
//          const btVector3& ptA = pt.getPositionWorldOnA(); ptA;
//
//
//
//          const btVector3& ptB = pt.getPositionWorldOnB(); ptB;
//          const btVector3& normalOnB = pt.m_normalWorldOnB; normalOnB;
//
//#if LOG_PHYSICS_MANAGER_COLLISIONS
//          DLog(eLogType::Info, "contact %d:", j);
//          DLog(eLogType::Info, "A pos: (%f, %f, %f)", ptA.getX(), ptA.getY(), ptA.getX());
//          DLog(eLogType::Info, "B pos: (%f, %f, %f)", ptB.getX(), ptB.getY(), ptB.getZ());
//          DLog(eLogType::Info, "B normal: (%f, %f, %f)", normalOnB.getX(), normalOnB.getY(), normalOnB.getZ());
//#endif
//        }
//      }
//    }

  }

  void syncPhysicsToGraphics()
  {
    /*auto rbWorld = m_dynamicsWorld;
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

        pCollider->SetOwnerEntityPosition(pos.getX(), pos.getY(), pos.getZ());
        pCollider->SetOwnerEntityRotation(rotX, rotY, rotZ);

      }
    }*/
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