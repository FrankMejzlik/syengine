#pragma once
#include "Component.h"

namespace SYE 
{

class PhysicsMaterial :
  public Component
{
public:
  PhysicsMaterial() = delete;

  PhysicsMaterial(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::PHYSICS_MATERIAL
  );
};

}