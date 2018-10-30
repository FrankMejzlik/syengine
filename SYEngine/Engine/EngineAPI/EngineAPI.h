
#pragma once

#include <queue>

#include "Scene.h"
#include "Command.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "NetworkManager.h"
#include "OutputManager.h"
#include "RenderingManager.h"
#include "SceneManager.h"
#include "SimulationManager.h"
#include "AudioManager.h"
#include "Engine.h"

using namespace SYE;

namespace SYE 
{

class EngineApi:
  public BaseModule
{
public:
  EngineApi() = delete;
  EngineApi(BaseModule &parentModule);
  ~EngineApi();


  virtual bool Initialize() override;
  virtual bool Terminate() override;



  uint64_t CreateBlock(
    glm::vec3 positionVector,
    glm::vec3 rotationVector,
    glm::vec3 scaleVector,
    dfloat width, dfloat height, dfloat length
  );


  static EngineApi* GetEngineApi()
  {
    return _pEngineApistatic;
  }



  /// vvvvvvvvvvvvvvvvvvvvvv
  template <typename T>
  bool PushEngineCommand(eCommandType type, std::vector<T> data)
  {
    Command cmd(type, data);
    _engineQueue.push(cmd);
    return true;
  }

  template <typename T, typename S>
  bool PushEngineCommand(eCommandType type, std::vector<T> data, std::vector<S> dataNext)
  {
    Command cmd(type, data, dataNext);
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
  static EngineApi* _pEngineApistatic;

  std::queue<Command> _engineQueue;
  std::queue<Command> _editorQueue;

  void SimulateEditorInput();

};

}