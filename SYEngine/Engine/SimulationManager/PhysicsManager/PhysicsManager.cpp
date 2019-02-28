#include "PhysicsManager.h"

#include "PhysicsScene.h"
#include "Scene.h"
#include "RenderingManager.h"

using namespace SYE;

PhysicsManager::PhysicsManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext),
  _pPhysicsScene(nullptr)
{
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::Success, "\t PhysicsManager instance created.");
}

PhysicsManager::~PhysicsManager() noexcept
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
  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t PhysicsManager instance terminated.");
  return true;
}


void PhysicsManager::InitializePhysicsScene(Scene* pScene)
{
  // Instantiate new PhysicsScene
  _pPhysicsScene = std::move(std::make_unique<PhysicsScene>(pScene));

  // Initiallize it
  _pPhysicsScene->Initialize();

  // Attach it to this Scene instance
  pScene->SetPhysicsScenePtr(_pPhysicsScene.get());

  // Setup DebugRenderer for this
  _pPhysicsScene->SetDebugRenderer(GetDebugRendererPtr());
}

PhysicsDebugRenderer* PhysicsManager::GetDebugRendererPtr() const
{
  BaseModule& engineModule = _parentModule.GetParentModuleRef();

  BaseModule* pOutputManager = engineModule.GetSubModulesRef()[ID_OUTPUT_MANAGER].get();

  BaseModule* pRenderingManager = pOutputManager->GetSubModulesRef()[ID_RENDERING_MANAGER].get();

  return static_cast<RenderingManager*>(pRenderingManager)->GetPhysicsDebugRendererPtr();
}

void PhysicsManager::TerminatePhysicsScene(Scene* pScene)
{
  UNREFERENCED_PARAMETER(pScene);

  // Free this PhysicsScene
  _pPhysicsScene.reset(nullptr);
}

void PhysicsManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{
  UNREFERENCED_PARAMETER(pScene);

  _pPhysicsScene->ProcessScene(deltaTime);
}