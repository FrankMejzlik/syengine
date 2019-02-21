#include "ScriptHandler.h"

#include "Script.h"

#include "script_includes.h"

using namespace SYE;

ScriptHandler::ScriptHandler(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
) noexcept:
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots)
{
  _type = eType::SCRIPT_HANDLER;
}

ScriptHandler::~ScriptHandler() noexcept
{}

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