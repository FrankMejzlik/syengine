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
class Scene;
class Window;

class Engine :
  public BaseEngine, public BaseModule
{
public:
  Engine() = delete;
  Engine(ProcessInstance* instance = nullptr) noexcept;
  virtual ~Engine() noexcept;

  virtual bool Initialize() override;
  virtual bool Terminate() override;
  virtual void TerminateGame() override;

  bool Run();


  EngineApi* GetEngineApiPtr() const;

  bool AttachScene(Scene* pScene);
  bool DetachScene(Scene* pScene);
  bool AttachWindow(Window* pWindow);
  bool DetachWindow(Window* pWindow);

private:
  void ProcessFrame(dfloat deltaTime, Scene* pScene, Window* pMainWindow);
  void ProcessImGui();
  void CheckModuleStates();
  Scene* AddScene(Window* pTargetWindow, size_t sceneId);
  Window* AddWindow();
  bool RemoveWindow(Window* pWindow);

  bool InitializeSceneInModules(Scene* pScene);


  // Attributes
private:
  // Instance that this Engine is running in.
  ProcessInstance* _pInstance;
  
  /** Engine context holding all engine relevant data that is needed across application */
  std::unique_ptr<EngineContext> _pOwningEngineContext;

  /** Windows attached to this Engine instance */
  std::map<size_t, Window*> _windows;

  /** Scenes attached to this Engine instance */
  std::map<size_t, Scene*> _scenes;

};

} // SYE