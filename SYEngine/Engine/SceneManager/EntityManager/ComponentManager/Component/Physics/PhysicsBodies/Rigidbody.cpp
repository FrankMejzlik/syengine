#include "Rigidbody.h"

#include "BlockCollider.h"
#include "SphereCollider.h"

#include "Scene.h"
#include "PhysicsScene.h"
#include "ConvexHullCollider.h"


using namespace SYE;

Rigidbody::Rigidbody(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  PhysicsBody(pOwnerEntity, pOwnerComponent, slotIndex, type)
{}


Rigidbody::~Rigidbody() noexcept
{}


void Rigidbody::SaveComponent()
{
  // Refresh quick links
  RefreshQuickRefs();

  // Try to delete this existing PhysicsEntity (if exists)
  GetOwnerScenePtr()->GetPhysicsScenePtr()->RemovePhysicsEntity(this);

  // Create new updated Physics Entity
  GetOwnerScenePtr()->GetPhysicsScenePtr()->InsertPhysicsEntity(this);
}

BlockCollider* Rigidbody::AddBlockCollider(dfloat width, dfloat height, dfloat length)
{
  BlockCollider* pBlockCollider = GetComponentManagerPtr()->CreateComponent<BlockCollider>(_pOwnerEntity, this);
  pBlockCollider->SetDimensions(width, height, length);
  pBlockCollider->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));

  _pCollider = static_cast<Collider*>(pBlockCollider);

  return pBlockCollider;
}

ConvexHullCollider* Rigidbody::AddConvexHullCollider(
  const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
  const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8
  )
{
  ConvexHullCollider* pBlockCollider = GetComponentManagerPtr()->CreateComponent<ConvexHullCollider>(_pOwnerEntity, this);
  
  std::vector<Vector3f> vec;
  vec.push_back(p1);
  vec.push_back(p2);
  vec.push_back(p3);
  vec.push_back(p4);
  vec.push_back(p5);
  vec.push_back(p6);
  vec.push_back(p7);
  vec.push_back(p8);

  pBlockCollider->SetVertices(vec);
  pBlockCollider->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));

  _pCollider = static_cast<Collider*>(pBlockCollider);

  return pBlockCollider;
}


SphereCollider* Rigidbody::AddSphereCollider(dfloat radius, size_t numSlices, size_t numStacks)
{
  SphereCollider* pSphereCollider = GetComponentManagerPtr()->CreateComponent<SphereCollider>(_pOwnerEntity, this);
  pSphereCollider->SetDimensions(radius, numSlices, numStacks);
  pSphereCollider->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));

  _pCollider = static_cast<Collider*>(pSphereCollider);

  return pSphereCollider;
}
