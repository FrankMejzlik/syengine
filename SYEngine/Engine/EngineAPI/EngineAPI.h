
#pragma once

#include <queue>

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

class EngineApi:
  public BaseModule
{
public:
  EngineApi() = delete;
  EngineApi(BaseModule &parentModule);
  ~EngineApi();

  virtual bool Initialize() override;
  virtual bool Terminate() override;



  /// vvvvvvvvvvvvvvvvvvvvvv
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

  void SimulateEditorInput();

};

}