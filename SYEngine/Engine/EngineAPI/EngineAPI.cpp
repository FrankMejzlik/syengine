
#include "Engine.h"
#include "EngineAPI.h"

using namespace SYE;


EngineApi* EngineApi::_pEngineApistatic = nullptr;


EngineApi::EngineApi(BaseModule &parentModule):
  BaseModule(parentModule),
  _engineQueue(),
  _editorQueue()
{

  _pEngineApistatic = this;


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

uint64_t EngineApi::CreateBlock(glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector, dfloat width, dfloat height, dfloat length)
{

  UNREFERENCED_PARAMETER(positionVector);
  UNREFERENCED_PARAMETER(rotationVector);
  UNREFERENCED_PARAMETER(scaleVector);
  UNREFERENCED_PARAMETER(width);
  UNREFERENCED_PARAMETER(height);
  UNREFERENCED_PARAMETER(length);

  return uint64_t();
}

void EngineApi::ProcessEngineQueue()
{
//  while (!_engineQueue.empty())
//  {
//
//    Command cmd(_engineQueue.front());
//    _engineQueue.pop();
//
//    auto data = cmd.GetFloatData();
//    Entity* newEntity;
//    std::vector<uint64_t> dataOut;
//    std::vector<std::string> stringData;
//
//    switch (cmd.GetType())  
//    {
//    case eCommandType::CreateBlock:
//
//      dataOut.push_back(newEntity->GetGuid());
//      PushEditorCommand<uint64_t>(eCommandType::CreatedObjectId, dataOut);
//      
//      break;
//
//    case eCommandType::CreateSphere:
//      //static_cast<Engine&>(_parentModule).HandleCommandCreateSphere(cmd.GetFloatData());
//      break;
//
//    case eCommandType::CreatePointLight:
//
//      break;
//
//    case eCommandType::CreateStaticModelFromFile:
//      stringData = cmd.GetStringData();
//
//      /*newEntity = SceneManager::GetActiveScene()->CreateStaticModelFromFile(
//        "staticModel",
//        glm::vec3(data[0], data[1], data[2]),
//        glm::vec3(data[3], data[4], data[5]),
//        glm::vec3(data[6], data[7], data[8]),
//        stringData[0]
//      );
//*/
//      dataOut.push_back(newEntity->GetGuid());
//      PushEditorCommand<uint64_t>(eCommandType::CreatedObjectId, dataOut);
//      break;
//
//    case eCommandType::CreateSpotLight:
//
//
//      break;
//
//    case eCommandType::DeleteObjectId:
//      //static_cast<Engine&>(_parentModule).HandleCommandDeleteObjectId(cmd.GetIntData());
//      break;
//
//    case eCommandType::Terminate:
//    
//      break;
//    }
//
//  }
}

std::queue<Command>* EngineApi::GetEditorCommandQueue()
{
  return &_editorQueue;
}

void SYE::EngineApi::SimulateEditorInput()
{


}

