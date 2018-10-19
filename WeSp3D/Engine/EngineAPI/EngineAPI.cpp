
#include "Engine.h"
#include "EngineAPI.h"

using namespace WeSp;

EngineAPI::EngineAPI(Engine* pParentInstance):
  IMainEngineModule(pParentInstance),
  _engineQueue(),
  _editorQueue()
{
  DLog(eLogType::Success, "EngineAPI instance created.");
}

EngineAPI::~EngineAPI()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "EngineAPI instance destroyed.");
}

bool EngineAPI::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in EngineAPI failed.");
    return false;
  }
  
  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "EngineAPI instance initialized.");
  return true;
}

bool EngineAPI::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EngineAPI instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "EngineAPI instance terminated.");
  return true;
}

void EngineAPI::ProcessEngineQueue()
{
  while (!_engineQueue.empty())
  {

    Command cmd(_engineQueue.front());
    _engineQueue.pop();

    switch (cmd.GetType())  
    {
    case eCommandType::CreateBlock:
      _pParentInstance->HandleCommandCreateBlock(cmd.GetFloatData());
      break;

    case eCommandType::CreateSphere:
      _pParentInstance->HandleCommandCreateSphere(cmd.GetFloatData());
      break;

    case eCommandType::CreatePointLight:

      break;

    case eCommandType::CreateSpotLight:


      break;

    case eCommandType::DeleteObjectId:
      _pParentInstance->HandleCommandDeleteObjectId(cmd.GetIntData());
      break;

    case eCommandType::Terminate:
    
      break;
    }

  }
}

std::queue<Command>* EngineAPI::GetEditorCommandQueue()
{
  return &_editorQueue;
}

