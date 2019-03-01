#pragma once

#include "common.h"
#include "Component.h"

namespace SYE
{

class Mesh;
class Rigidbody;
class Transform;

class Collider :
  public Component
{
  // Methods
public:
  Collider() = delete;
  Collider(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::COLLIDER
  );
  virtual ~Collider() noexcept;


  void SetMeshPtr(Mesh* pMesh);
  void ClearMesh();

  const std::vector<unsigned int>& GetIndices() const;
  const std::vector<dfloat>& GetVertices() const;

  const Vector3f& GetWorldPositionConstRef() const;
  const Vector3f& GetWorldRotationConstRef() const;
  const Vector3f& GetWorldScaleConstRef() const;

  void SetIsTrigger(bool newValue);
  bool IsTrigger() const;

  void SetLocalPosition(Vector3f position);
  void SetLocalRotation(Vector3f rotation);
  void SetLocalScale(Vector3f scale);

  void SetTransformPosition(dfloat x, dfloat y, dfloat z);
  void SetTransformRotation(dfloat x, dfloat y, dfloat z);
  void SetTransformScale(dfloat x, dfloat y, dfloat z);

protected:
  void RecalculateAbsolutePosition();
  void RecalculateAbsoluteRotation();
  void RecalculateAbsoluteScale();




  // Attributes
protected:
  Mesh* _pMesh;
  bool _isTrigger;

  Vector3f _localPosition;
  Vector3f _localRotation;
  Vector3f _localScale;

  Vector3f _worldPosition;
  Vector3f _worldRotation;
  Vector3f _worldScale;

};

} // namespace SYE