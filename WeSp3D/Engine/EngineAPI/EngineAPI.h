
#pragma once

#include <queue>

#include "IMainEngineModule.h"

#include "Command.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "NetworkManager.h"
#include "OutputManager.h"
#include "RenderingManager.h"
#include "SceneManager.h"
#include "SimulationManager.h"
#include "AudioManager.h"

using namespace WeSp;

namespace WeSp 
{

class Engine;

class EngineAPI:
  public IMainEngineModule, public IModuleState, public IErrorLogging
{
public:
  EngineAPI() = delete;
  EngineAPI(Engine* pParentInstance);
  ~EngineAPI();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules) override;
  virtual bool Terminate() override;

  template <typename T>
  bool PushEngineCommand(eCommandType type, std::vector<T> data)
  {
    Command cmd(type, data);
    _engineQueue.push(cmd);
    return true;
  }

  template <typename T>
  bool PushEditorCommand(eCommandType type, std::vector<T> data)
  {
    Command cmd(type, data);
    _editorQueue.push(cmd);
    return true;
  }

  bool PushEditorCommand(eCommandType type)
  {
    Command cmd(type);
    _editorQueue.push(cmd);
    return true;
  }


  void ProcessEngineQueue();

  std::queue<Command>* GetEditorCommandQueue();

private:
  std::queue<Command> _engineQueue;
  std::queue<Command> _editorQueue;

};

}