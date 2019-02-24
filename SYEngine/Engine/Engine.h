#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <map>

// Project includes.
#include "macros.h"
#include "config_engine.h"
#include "config_world.h"

#include "IModuleState.h"
#include "IErrorLogging.h"

#include "Logger.h"
#include "TimeManager.h"
#include "EngineContext.h"
#include "GameContext.h"
#include "SceneContext.h"
#include "BaseEngine.h"
#include "Instance.h"

// Modules.
#include "EngineAPI.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "NetworkManager.h"
#include "OutputManager.h"
#include "RenderingManager.h"
#include "LogicManager.h"
#include "SceneManager.h"
#include "SimulationManager.h"
#include "AudioManager.h"
#include "ComponentManager.h"


using namespace SYE;

namespace SYE
{

class Window;

class Engine :
  public BaseEngine, public BaseModule
{
public:
  Engine() = delete;
  Engine(ProcessInstance* instance) noexcept;
  virtual ~Engine() noexcept;

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool Run();

  EngineApi* GetEngineApiPtr() const;
  SceneManager* GetSceneManagerPtr() const;

  

private:
  // Instance that this Engine is running in.
  ProcessInstance* _pInstance;
  // Engine context instance.
  EngineContext _engineContext;

  void ProcessFrame(dfloat deltaTime, Scene* pScene, Window* pMainWindow);
  void ProcessImGui();
  void CheckModuleStates();

public:
  GameContext _gameContext;

};

} // SYE