#include "Script.h"

#include "Scene.h"
#include "Transform.h"

using namespace SYE;

Script::Script(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
) noexcept :
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots, false) 
{
  _type = eType::SCRIPT;
}


Script::~Script() noexcept
{}

void Script::Refresh()
{
  /**
   * Update all quick refs to sibling Components
   */

  // Update Transform quick ref
  if (!_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].empty())
  {
    _pTransform = static_cast<Transform*>(_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].begin()->second);
  }

}