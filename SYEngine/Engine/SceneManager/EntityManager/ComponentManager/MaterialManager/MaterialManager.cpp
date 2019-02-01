#include "MaterialManager.h"

using namespace SYE;

MaterialManager::MaterialManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  //_subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_unique<AIManager>(this)));
  //_subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_unique<LogicManager>(this)));
  
  //_genericMaterials.insert(std::make_pair(std::string("shiny_material"), std::make_unique<Material>(1.0f, 512)));
  //_genericMaterials.insert(std::make_pair(std::string("dull_material"), std::make_unique<Material>(0.3f, 4)));

  DLog(eLogType::Success, "\t\t\t MaterialManager instance created.");
}

MaterialManager::~MaterialManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t\t\t MaterialManager instance destroyed.");
}

bool MaterialManager::Initialize()
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

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t\t\t MaterialManager instance initialized.");
  return true;
}

bool MaterialManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t\t\t MaterialManager instance terminated.");
  return true;
}

std::shared_ptr<Material> MaterialManager::GetDefaultMaterial() const
{
  return _genericMaterials.find(std::string("shiny_material"))->second;
}