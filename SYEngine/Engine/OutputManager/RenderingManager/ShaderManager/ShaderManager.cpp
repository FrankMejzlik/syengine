#include "ShaderManager.h"

#include "Shader.h"

using namespace SYE;

ShaderManager::ShaderManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "\t\t ShaderManager instance created.");
}

ShaderManager::~ShaderManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::cSuccess, "\t\t ShaderManager instance destroyed.");
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


  SetModuleState(eModuleState::OK);
  DLog(eLogType::cSuccess, "\t\t ShaderManager instance initialized.");
  return true;
}

bool ShaderManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "\t\t ShaderManager instance terminated.");
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
  std::vector<NewShader::eUniforms> _requiredUniforms,
  std::vector<NewShader::eUniforms> _optionalUniforms,
  std::string_view vsFilepath,
  std::string_view fsFilepath,
  std::string_view tsFilepath,
  std::string_view gsFilepath
)
{
  // Instantiate new Shader instance
  std::unique_ptr<NewShader> pShader = std::make_unique<NewShader>(
    _requiredUniforms, _optionalUniforms,
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

bool ShaderManager::InitializeScene(Scene* pScene)
{
  UNREFERENCED_PARAMETER(pScene);

  bool result = true;

  // Load standard Shaders
  result = result && LoadStandardShaders();

  return result;
}

bool ShaderManager::LoadStandardShaders()
{
  bool result = true;

  ////////////////////////////////////////////////
  // 0: StandardShader
  ////////////////////////////////////////////////
  
  // Required uniforms
  std::vector<NewShader::eUniforms> requiredUniformsShader0;
  requiredUniformsShader0.push_back(NewShader::eUniforms::cMVPTransformMatrixPerspective);
  requiredUniformsShader0.push_back(NewShader::eUniforms::cMVPTransformMatrixDirLights);
  requiredUniformsShader0.push_back(NewShader::eUniforms::cModelToWorldTransformMatrix);

  requiredUniformsShader0.push_back(NewShader::eUniforms::cDirectionalLights);
  requiredUniformsShader0.push_back(NewShader::eUniforms::cDiffuseTexture);
  requiredUniformsShader0.push_back(NewShader::eUniforms::cNormalMapTexture);

  requiredUniformsShader0.push_back(NewShader::eUniforms::cDirectionalLightShadowMaps);
  requiredUniformsShader0.push_back(NewShader::eUniforms::cMaterial);
  requiredUniformsShader0.push_back(NewShader::eUniforms::cEyePosition);

  // Optional uniforms
  std::vector<NewShader::eUniforms> optionalUniformsShader0;

  NewShader* pShader = CreateShader(
    requiredUniformsShader0, optionalUniformsShader0,
    CONCATENATE_DEFINES(PATH_SHADERS, STANDARD_SHADER_VS_FILENAME),
    CONCATENATE_DEFINES(PATH_SHADERS, STANDARD_SHADER_FS_FILENAME)
  );
  if (pShader == nullptr)
  {
    result = false;
  }
  _systemShaders.push_back(pShader);


  ////////////////////////////////////////////////
  // 1: StandardOrthoShadowMapShader
  ////////////////////////////////////////////////

  // Required uniforms
  std::vector<NewShader::eUniforms> requiredUniformsShader1;
  requiredUniformsShader1.push_back(NewShader::eUniforms::cMVPTransformMatrixOrtho);

  // Optional uniforms
  std::vector<NewShader::eUniforms> optionalUniformsShader1;
  optionalUniformsShader1.push_back(NewShader::eUniforms::cMVPTransformMatrixOrtho);

  
  pShader = CreateShader(
    requiredUniformsShader1, optionalUniformsShader1,
    CONCATENATE_DEFINES(PATH_SHADERS, STANDARD_SHADER_VS_SM_ORTHO_FILENAME),
    CONCATENATE_DEFINES(PATH_SHADERS, STANDARD_SHADER_FS_SM_ORTHO_FILENAME)
  );
  if (pShader == nullptr)
  {
    result = false;
  }
  _systemShaders.push_back(pShader);


  ////////////////////////////////////////////////
  // 2: StandardPerspectiveShadowMapShader
  ////////////////////////////////////////////////
  std::vector<NewShader::eUniforms> requiredUniformsShader2;
  requiredUniformsShader2.push_back(NewShader::eUniforms::cMVPTransformMatrixPerspective);
  requiredUniformsShader2.push_back(NewShader::eUniforms::cEyePosition);


  std::vector<NewShader::eUniforms> optionalUniformsShader2;
  optionalUniformsShader2.push_back(NewShader::eUniforms::cEyePosition);

  pShader = CreateShader(
    requiredUniformsShader2, optionalUniformsShader2,
    CONCATENATE_DEFINES(PATH_SHADERS, STANDARD_SHADER_VS_SM_PERSPECTIVE_FILENAME),
    CONCATENATE_DEFINES(PATH_SHADERS, STANDARD_SHADER_FS_SM_PERSPECTIVE_FILENAME),
    std::string_view(),
    CONCATENATE_DEFINES(PATH_SHADERS, STANDARD_SHADER_GS_SM_PERSPECTIVE_FILENAME)
  );
  if (pShader == nullptr)
  {
    result = false;
  }
  _systemShaders.push_back(pShader);


  // If something failed
  if (!result)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::FailedToLoadSystemShaders,
      std::string("Failed to load system Shaders "),
      std::string("REASON: Some of CreateShader() failed.")
    );
    SetState(eState::cError);
  }

  return result;
}

NewShader* ShaderManager::GetStandardShader() const
{
  return _systemShaders[STANDARD_SHADER_INDEX];
}

NewShader* ShaderManager::GetStandardOrthoShadowMapShader() const
{
  return _systemShaders[STANDARD_SHADOW_MAP_ORTHO_SHADER_INDEX];
}

NewShader* ShaderManager::GetStandardPerspectiveShadowMapShader() const
{
  return _systemShaders[STANDARD_SHADOW_MAP_PERSPECTIVE_SHADER_INDEX];
}