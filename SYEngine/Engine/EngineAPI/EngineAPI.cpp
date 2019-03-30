
#include "Engine.h"
#include "EngineAPI.h"

using namespace SYE;


EngineApi* EngineApi::_pEngineApistatic = nullptr;


EngineApi::EngineApi(BaseModule &parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext),
  _engineQueue(),
  _editorQueue()
{

  _pEngineApistatic = this;

  DLog(eLogType::cSuccess, "EngineAPI instance created.");
}

EngineApi::~EngineApi()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "EngineAPI instance destroyed.");
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
  DLog(eLogType::cSuccess, "EngineAPI instance initialized.");
  return true;
}

bool EngineApi::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "EngineAPI instance terminated.");
  return true;
}

uint64_t EngineApi::CreateBlock([[maybe_unused]] glm::vec3 positionVector, [[maybe_unused]] glm::vec3 rotationVector, [[maybe_unused]] glm::vec3 scaleVector, [[maybe_unused]] dfloat width, [[maybe_unused]] dfloat height, [[maybe_unused]] dfloat length)
{


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

