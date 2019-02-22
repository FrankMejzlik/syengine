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
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
  ) noexcept;
  virtual ~Collider() = default;


  virtual void Refresh() override;

  const std::vector<unsigned int>& GetIndices() const;
  const std::vector<dfloat>& GetVertices() const;

  const Vector3f& GetWorldPositionConstRef() const;
  const Vector3f& GetWorldRotationConstRef() const;
  const Vector3f& GetWorldScaleConstRef() const;

  bool IsTrigger() const;

  void RecalculateAbsolutePosition();
  void RecalculateAbsoluteRotation();


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


  /**
   * QUICK REFERENCES
   */
  /** Sibling Transform Component */
  Transform* _pTransform;
  /** Sibling Rigidbody Component */
  Rigidbody* _pRigidbody;
};

} // namespace SYE