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

      for (int i = 0; i < count; i = i + 3)
      {
        mesh->addTriangle(
          btVector3(vertices[indices[i * 8]], vertices[indices[indices[i * 8 + 1]]], indices[indices[i * 8 + 2]]),
          btVector3(vertices[indices[(i + 1) * 8]], vertices[indices[indices[(i + 1) * 8 + 1]]], indices[indices[(i + 1) * 8 + 2]]),
          btVector3(vertices[indices[(i + 2) * 8]], vertices[indices[indices[(i + 2) * 8 + 1]]], indices[indices[(i + 2) * 8 + 2]])
        );
      }
      btBvhTriangleMeshShape* trimesh = new btBvhTriangleMeshShape(mesh, true, true);


      m_collisionShapes.push_back(trimesh);

    }

  }


  void syncPhysicsToGraphics(const btDiscreteDynamicsWorld* rbWorld)
  {

    int numCollisionObjects = rbWorld->getNumCollisionObjects();
    {
      
      for (int i = 0; i < numCollisionObjects; i++)
      {

        btCollisionObject* colObj = rbWorld->getCollisionObjectArray()[i];
        btCollisionShape* collisionShape = colObj->getCollisionShape();


        btVector3 pos = colObj->getWorldTransform().getOrigin();
        btQuaternion orn = colObj->getWorldTransform().getRotation();
        int index = colObj->getUserIndex();

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