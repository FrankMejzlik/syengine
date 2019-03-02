
#include "ConvexHullCollider.h"
#include "ComponentManager.h" 

#include "Mesh.h"

using namespace SYE;

ConvexHullCollider::ConvexHullCollider(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Collider(pOwnerEntity, pOwnerComponent, slotIndex, type)
{}

void ConvexHullCollider::SetVertices(const std::vector<Vector3f>& vertices)
{
  _vertices = vertices;

  // Clear old Mesh
  ClearMesh();

  // Create new Mesh
  Mesh* pMesh = GetComponentManagerPtr()->CreateComponent<Mesh>(_pOwnerEntity, this);
  // Make it desired sphere
  // TODO: Accept any number of vertices
  pMesh->MakePrism(vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7]);

  // Add it as Mesh for Collider
  SetMeshPtr(pMesh);
}

void ConvexHullCollider::SetVertices(std::vector<Vector3f>&& vertices)
{
  _vertices = std::move(vertices);

  // Clear old Mesh
  ClearMesh();

  // Create new Mesh
  Mesh* pMesh = GetComponentManagerPtr()->CreateComponent<Mesh>(_pOwnerEntity, this);
  // Make it desired sphere
  // TODO: Accept any number of vertices
  pMesh->MakePrism(vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7]);

  // Add it as Mesh for Collider
  SetMeshPtr(pMesh);
}

