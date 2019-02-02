#include "PhysicsManager.h"

using namespace SYE;

PhysicsManager::PhysicsManager(BaseModule &parentModule):
  BaseModule(parentModule),
  _bulletPhysics(nullptr)
{

  DLog(eLogType::Success, "\t PhysicsManager instance created.");
}

PhysicsManager::~PhysicsManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t PhysicsManager instance destroyed.");
}

bool PhysicsManager::Initialize()
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
  DLog(eLogType::Success, "\t PhysicsManager instance initialized.");
  return true;
}

bool PhysicsManager::Terminate()
{
  // Class specific terminate
  _bulletPhysics.exitPhysics();

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t PhysicsManager instance terminated.");
  return true;
}


void PhysicsManager::InitializePhysicsScene(Scene* pScene)
{
  _bulletPhysics.SetScene(pScene);
  _bulletPhysics.initPhysics();
}

void PhysicsManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{
  UNREFERENCED_PARAMETER(pScene);


  _bulletPhysics.stepSimulation(deltaTime);
  _bulletPhysics.syncPhysicsToGraphics();


  


}