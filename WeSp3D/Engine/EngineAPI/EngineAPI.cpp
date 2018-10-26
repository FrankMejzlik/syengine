
#include "Engine.h"
#include "EngineAPI.h"

using namespace WeSp;

EngineApi::EngineApi(BaseModule &parentModule):
  BaseModule(parentModule),
  _engineQueue(),
  _editorQueue()
{
  DLog(eLogType::Success, "EngineAPI instance created.");
}

EngineApi::~EngineApi()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "EngineAPI instance destroyed.");
}

bool EngineApi::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "EngineAPI instance initialized.");
  return true;
}

bool EngineApi::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "EngineAPI instance terminated.");
  return true;
}

void EngineApi::ProcessEngineQueue()
{
  while (!_engineQueue.empty())
  {

    Command cmd(_engineQueue.front());
    _engineQueue.pop();

    switch (cmd.GetType())  
    {
    case eCommandType::CreateBlock:
      //static_cast<Engine&>(_parentModule).HandleCommandCreateBlock(cmd.GetFloatData());
      
      break;

    case eCommandType::CreateSphere:
      //static_cast<Engine&>(_parentModule).HandleCommandCreateSphere(cmd.GetFloatData());
      break;

    case eCommandType::CreatePointLight:

      break;

    case eCommandType::CreateSpotLight:


      break;

    case eCommandType::DeleteObjectId:
      //static_cast<Engine&>(_parentModule).HandleCommandDeleteObjectId(cmd.GetIntData());
      break;

    case eCommandType::Terminate:
    
      break;
    }

  }
}

std::queue<Command>* EngineApi::GetEditorCommandQueue()
{
  return &_editorQueue;
}

void WeSp::EngineApi::SimulateEditorInput()
{


}

