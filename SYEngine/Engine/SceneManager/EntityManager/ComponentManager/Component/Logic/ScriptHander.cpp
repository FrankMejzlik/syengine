
#include "ScriptHandler.h"

#include "Script.h"

#include "generic_script_includes.h"

using namespace SYE;

ScriptHandler::ScriptHandler(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
):
  Component(pOwnerEntity, pOwnerComponent, true, true, slotIndex, type)
{}

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
