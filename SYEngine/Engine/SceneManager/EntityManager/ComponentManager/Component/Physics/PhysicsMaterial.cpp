#include "PhysicsMaterial.h"

using namespace SYE;

PhysicsMaterial::PhysicsMaterial(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type)
{}
