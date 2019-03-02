#pragma once

#include <vector>

#include "common.h"
#include "Collider.h"

namespace SYE
{

class ConvexHullCollider :
  public Collider
{
public:
  ConvexHullCollider() = delete;
  ConvexHullCollider(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = PHYSICS_COLLIDER, Component::eType type = eType::CONVEX_HULL_COLLIDER
  );
  virtual ~ConvexHullCollider() noexcept = default;

  void SetVertices(const std::vector<Vector3f>& vertices);
  void SetVertices(std::vector<Vector3f>&& vertices);
  const std::vector<Vector3f>& GetVerticesConstRef() const
  {
    return _vertices;
  }


  // Attributes
protected:
  std::vector<Vector3f> _vertices;

};

} // namespace SYE