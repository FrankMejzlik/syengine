#include "ScriptManager.h"

#include "Scene.h"
#include "ScriptHandler.h"

using namespace SYE;

ScriptManager::ScriptManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Enlist all submodules into EngineContext ptr table

  EnlistSubmodulesToEngineContext();
  DLog(eLogType::Success, "\t ScriptManager instance created.");
}

ScriptManager::~ScriptManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t ScriptManager instance destroyed.");
}

bool ScriptManager::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }
  // Class specific initialization

  SetModuleState(eModuleState::OK);
  DLog(eLogType::Success, "\t ScriptManager instance initialized.");
  return true;
}

bool ScriptManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t ScriptManager instance terminated.");
  return true;
}

void ScriptManager::InitializeScene(Scene * pScene)
{
  // Trigger OnInitialize on Components
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActiveComponentsBySlotsRef();

  // Iterate through all active scripts and process them
  for (auto&& script : components[COMPONENT_SCRIPT_HANDLER_SLOT])
  {
    static_cast<ScriptHandler*>(script.second)->TriggerOnInitializeScene();
  }
}

void ScriptManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{
  UNREFERENCED_PARAMETER(deltaTime);
  UNREFERENCED_PARAMETER(pScene);

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActiveComponentsBySlotsRef();

  // Iterate through all active scripts and process them
  for (auto&& script : components[COMPONENT_SCRIPT_HANDLER_SLOT])
  {
    static_cast<ScriptHandler*>(script.second)->TriggerOnProcessFrame(deltaTime, pScene);
  }

}