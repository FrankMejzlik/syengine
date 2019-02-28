#pragma once

#include "common.h"
#include "Component.h"


namespace SYE 
{

class Collider;
class PhysicsEntity;
class Transform;

class PhysicsBody:
  public Component
{
public:
  PhysicsBody() = delete;
  PhysicsBody(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::PHYSICS_BODY
  );

  virtual void SaveComponent() override;
  virtual void Refresh() override;

  void SetCollider(Collider* pCollider);
  Collider* GetCollider() const { return _pCollider; }
  bool HasCollider() const;
  void SetMass(dfloat mass);
  dfloat GetMass() const { return _mass; }
  bool IsStatic() const;
  bool IsDynamic() const;
  void SetIsKinematic(bool isKinematic);
  bool IsKinematic() const;

  void ClearCollider();
  
  void SetPhysicsEntity(PhysicsEntity* pPhysEntity);
  PhysicsEntity* GetPhysicsEntity() const;
  
  Transform* GetTransformPtr() const { return _pTransform; }


  // Attributes
protected:
  /** Collider for this body */
  Collider* _pCollider;

  /** Pointer to PhysicsEntity instance used for simulation */
  PhysicsEntity* _pPhysEntity;

  /** Mass of this body */
  dfloat _mass;

  /** If is kinematic (must also have zero mass)*/
  bool _isKinematic;

private:
  Transform* _pTransform;

};

}