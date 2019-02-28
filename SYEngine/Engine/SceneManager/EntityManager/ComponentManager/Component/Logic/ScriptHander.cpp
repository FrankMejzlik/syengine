#include "ScriptHandler.h"

#include "Script.h"

#include "script_includes.h"

using namespace SYE;

ScriptHandler::ScriptHandler(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
  eSlotIndex slotIndex, Component::eType type
):
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots, true, true, slotIndex, type)
{

}

ScriptHandler::~ScriptHandler() noexcept
{}

void ScriptHandler::Refresh()
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

void ScriptHandler::ClearScript() 
{ 
  _pScript = nullptr; 
}

void ScriptHandler::TriggerOnInitializeScene()
{
  _pScript->OnInitializeScene();
}

void ScriptHandler::TriggerOnProcessFrame(dfloat deltaTime, Scene* pScene)
{
  _pScript->OnProcessFrame(deltaTime, pScene);
}

Transform* ScriptHandler::GetTransformPtr()
{
  return _pTransform;
}