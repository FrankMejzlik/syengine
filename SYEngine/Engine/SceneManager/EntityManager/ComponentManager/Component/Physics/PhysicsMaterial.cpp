#include "PhysicsMaterial.h"

using namespace SYE;

PhysicsMaterial::PhysicsMaterial(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
  eSlotIndex slotIndex, Component::eType type
):
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots, false, true, slotIndex, type)
{}
