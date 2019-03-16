#include "ShaderManager.h"

#include "Shader.h"

using namespace SYE;

ShaderManager::ShaderManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::Success, "\t\t ShaderManager instance created.");
}

ShaderManager::~ShaderManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t\t ShaderManager instance destroyed.");
}

bool ShaderManager::Initialize()
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
  DLog(eLogType::Success, "\t\t ShaderManager instance initialized.");
  return true;
}

bool ShaderManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t\t ShaderManager instance terminated.");
  return true;
}

void ShaderManager::TerminateGame()
{
  // Delete all shaders
  ClearShaders();
}

void ShaderManager::ClearShaders()
{
  _shaders.clear();
}

NewShader* ShaderManager::CreateShader(
  std::string_view vsFilepath,
  std::string_view fsFilepath,
  std::string_view tsFilepath,
  std::string_view gsFilepath
)
{
  // Instantiate new Shader instance
  std::unique_ptr<NewShader> pShader = std::make_unique<NewShader>(
    vsFilepath, fsFilepath,
    tsFilepath, gsFilepath
  );

  auto result = _shaders.insert(std::make_pair(pShader->GetGuid(), std::move(pShader)));

  // If item wasl already present
  if (result.second == false)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::AddingAlreadyExistingShader,
      std::string("Shader with ID ") + std::to_string(result.first->first) + std::string(" already exists."),
      ""
    );

    SetState(eState::cWarning);
  }

  return result.first->second.get();
}