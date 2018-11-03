#pragma once

#include "BaseModule.h"

#include "Scene.h"

// Include Bullet3 headers.
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "bullet3parts/CommonRigidBodyBase.h"

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
    DLog(eLogType::Info, "collision on objs %d, %d", partId0, partId1);
    return true;
  }

  void SetScene(std::shared_ptr<Scene> pScene)
  {
    _pScene = pScene;
  }
  std::shared_ptr<Scene> _pScene;

  

  virtual void initPhysics()
  {

    auto colliders = _pScene->GetActiveColliders();

    createEmptyDynamicsWorld();

    for (auto && it : colliders)
    {

      std::shared_ptr<Collider> collider = it.second;

      std::vector<GLfloat> vertices = collider->GetVertices();
      std::vector<unsigned int> indices = collider->GetIndices();

      size_t count = indices.size();

      btTriangleMesh* mesh = new btTriangleMesh();

      DLog(eLogType::Info, "Constructing mesh for Bullet3");

      for (int i = 0; i < count; i = i + 3)
      {
        DLog(eLogType::Info, "triangle %d:", i / 3);
        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i] * 8], vertices[indices[i] * 8 + 1], vertices[indices[i] * 8 + 2]);
        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i + 1] * 8], vertices[indices[i + 1] * 8 + 1], vertices[indices[i + 1] * 8 + 2]);
        DLog(eLogType::Info, "v1: (%f, %f, %f)", vertices[indices[i + 2] * 8], vertices[indices[i + 2] * 8 + 1], vertices[indices[i + 2] * 8 + 2]);
        

        mesh->addTriangle(
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
      DLog(eLogType::Info, "------------------------");
      //btBvhTriangleMeshShape* trimesh = new btBvhTriangleMeshShape(mesh, true, true);
      btConvexShape* trimesh = new btConvexTriangleMeshShape(mesh);
      m_collisionShapes.push_back(trimesh);

      // Create rigidbody
      btTransform transform;
      transform.setIdentity();
      transform.setOrigin(
        btVector3(
          collider->GetAbsolutePositionConstRef().x, 
          collider->GetAbsolutePositionConstRef().y,
          collider->GetAbsolutePositionConstRef().z
        )
      );
      transform.setRotation(
        btQuaternion(
          collider->GetAbsoluteRotationConstRef().x,
          collider->GetAbsoluteRotationConstRef().y,
          collider->GetAbsoluteRotationConstRef().z
        )
      );

      btScalar mass(1.0f);
      auto newRb = createRigidBody(mass, transform, trimesh, btVector4(0, 0, 1, 1));
      newRb->setUserIndex(static_cast<int>(collider->GetGuid()));
      newRb->setUserPointer(collider.get());
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
        btCollisionShape* collisionShape = colObj->getCollisionShape();


        btVector3 pos = colObj->getWorldTransform().getOrigin();
        btQuaternion orn = colObj->getWorldTransform().getRotation();
        
        btScalar rotX, rotY, rotZ;
        orn.getEulerZYX(rotX, rotY, rotZ);


        Collider* pCollider = static_cast<Collider*>(colObj->getUserPointer());

        pCollider->SetOwnerEntityPosition(pos.getX(), pos.getY(), pos.getZ());
        pCollider->SetOwnerEntityRotation(rotX, rotY, rotZ);

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

  void InitializePhysicsScene(std::shared_ptr<Scene> pScene);

  void ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene);


private:
  Bullet3Wrapper _bulletPhysics;
};

}