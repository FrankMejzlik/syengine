#include "RenderingManager.h"

using namespace WeSp;

RenderingManager::RenderingManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Add submodules for this module.
  _subModules.insert(std::make_pair(ID_WINDOW_MANAGER, std::make_shared<WindowManager>(*this)));
  _subModules.insert(std::make_pair(ID_SHADOW_MANAGER, std::make_shared<ShadowManager>(*this)));
  
  DLog(eLogType::Success, "\t RenderingManager instance created.");
}

RenderingManager::~RenderingManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t RenderingManager instance destroyed.");
}

bool RenderingManager::Initialize()
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

  

  //

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t RenderingManager instance initialized.");
  return true;
}

bool RenderingManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t RenderingManager instance terminated.");
  return true;
}

std::shared_ptr<Window> RenderingManager::ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height)
{
  auto tmp = WINDOW_MANAGER->ConstructWindow(windowType, windowTitle, width, height);
  CreateShaders();
  return tmp;
}

void RenderingManager::RenderScene(std::shared_ptr<Scene> pScene, std::shared_ptr<Window> pTargetWindow)
{
  if (!_perspectiveProjectionMatrixInitialized)
  {
    // Get projeciton matrix
    _perspectiveProjectionMatrix = glm::perspective(
      glm::radians(45.0f),
      (GLfloat)(pTargetWindow->GetBufferWidth()) / pTargetWindow->GetBufferHeight(),
      0.1f, 100.0f
    );
    _perspectiveProjectionMatrixInitialized = true;
  }

  if (!_orthoProjectionMatrixInitialized)
  {
    // Get projeciton matrix
    _orthoProjectionMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
    _orthoProjectionMatrixInitialized = true;
  }


  // Calculate directional light shadow maps
  DirectionalShadowMapPass(pScene->GetActiveModelsRefConst(), pScene->GetDirectionalLightsMapRefConst());

  // Calculate point light shadow maps
  OmniShadowMapPass(pScene->GetActiveModelsRefConst(), pScene->GetPointLightsMapRefConst());


  // Render actual scene with computed shadow maps
  FinalMainRenderPass(
    pScene->GetActiveModelsRefConst(), 
    pScene,  
    pScene->GetDirectionalLightsMapRefConst(), 
    pScene->GetPointLightsMapRefConst(), 
    pScene->GetSpotLightsMapRefConst());

}

void RenderingManager::CreateShaders()
{
  const char* vShader = "shaders/shader.vert";
  const char* fShader = "shaders/shader.frag";
  const char* vDLShader = "shaders/directional_shadow_map.vert";
  const char* fDLShader = "shaders/directional_shadow_map.frag";
  const char* vODLShader = "shaders/omni_shadow_map.vert";
  const char* gODLShader = "shaders/omni_shadow_map.geom";
  const char* fODLShader = "shaders/omni_shadow_map.frag";

  std::shared_ptr<Shader> pMainShader = std::make_shared<Shader>();
  pMainShader->CreateFromFiles(vShader, fShader);
  _shaders.push_back(pMainShader);

  std::shared_ptr<Shader> pDLShader = std::make_shared<Shader>();
  pDLShader->CreateFromFiles(vDLShader, fDLShader);
  _shaders.push_back(pDLShader);

  std::shared_ptr<Shader> pODLShader = std::make_shared<Shader>();
  pODLShader->CreateFromFiles(vODLShader, gODLShader, fODLShader);
  _shaders.push_back(pODLShader);

}

void WeSp::RenderingManager::DirectionalShadowMapPass(const std::unordered_map<size_t, std::shared_ptr<Entity>>& activeModels, const std::unordered_map<size_t, std::shared_ptr<Entity>>& directionalLights)
{
  _shaders[1]->UseShader();

  for (auto it : directionalLights)
  {
    std::shared_ptr<DirectionalLight> light = std::static_pointer_cast<DirectionalLight>(it.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    uniformModel = _shaders[1]->GetModelLocation();


    // Give it correctly calculated lightTransform matrix
    _shaders[1]->SetDirectionalLightTransform(&light->CalculateLightTransform());

    _shaders[1]->Validate();
    // Render objects in scene with their own shaders

    for (auto it : activeModels)
    {
      std::shared_ptr<Model> model;
      model = std::static_pointer_cast<Model>(it.second->GetModel());
      model->RenderModel(uniformModel);

    }
  }

  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void WeSp::RenderingManager::OmniShadowMapPass(const std::unordered_map<size_t, std::shared_ptr<Entity>>& activeModels, const std::unordered_map<size_t, std::shared_ptr<Entity>>& omniDirectionalLights)
{
  _shaders[2]->UseShader();

  for (auto it : omniDirectionalLights)
  {
    std::shared_ptr<SpotLight> light = std::static_pointer_cast<SpotLight>(it.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    uniformModel = _shaders[2]->GetModelLocation();
    uniformOmniLightPos = _shaders[2]->GetOmniLightPosLocation();
    uniformFarPlane = _shaders[2]->GetFarPlaneLocation();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
    glUniform1f(uniformFarPlane, light->GetFarPlane());

    // Bind to shader 6 direction transofrm light metrices
    _shaders[2]->SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    _shaders[2]->Validate();

    // Render objects in scene with their own shaders

    for (auto it : activeModels)
    {
      std::shared_ptr<Model> model;
      model = std::static_pointer_cast<Model>(it.second->GetModel());
      model->RenderModel(uniformModel);

    }
  }

  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void WeSp::RenderingManager::FinalMainRenderPass(const std::unordered_map<size_t, 
  std::shared_ptr<Entity>>& activeModels, std::shared_ptr<Scene> pScene, 
  const std::unordered_map<size_t, std::shared_ptr<Entity>>& directionalLights,
  const std::unordered_map<size_t, std::shared_ptr<Entity>>& pointLights,
  const std::unordered_map<size_t, std::shared_ptr<Entity>>& spotLights
)
{
  std::shared_ptr<DirectionalLight> mainLight = std::static_pointer_cast<DirectionalLight>(directionalLights.begin()->second);

  // Set correct viewport, just to be sure
  glViewport(0, 0, GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);

  // Clear window
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw main scene
  _shaders[0]->UseShader();
  uniformModel = _shaders[0]->GetModelLocation();
  uniformProjection = _shaders[0]->GetProjectionLocation();
  uniformView = _shaders[0]->GetViewLocation();
  uniformEyePosition = _shaders[0]->GetEyePosition();
  //uniformSpecularIntensity = _shaders[0]->GetSpecularIntensityLocation();
  //uniformShininess = _shaders[0]->GetShininessLocation();

  // Set values in shader uniforms
  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(_perspectiveProjectionMatrix));
  glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(pScene->GetEditorCamera()->CalculateViewMatrix()));
  glUniform3f(uniformEyePosition, 
    pScene->GetEditorCamera()->GetCameraPosition().x, 
    pScene->GetEditorCamera()->GetCameraPosition().y, 
    pScene->GetEditorCamera()->GetCameraPosition().z
  );

  // Get counts of lights.
  int pointLightCount = pointLights.size();
  int spotLightCount = spotLights.size();


  // Set up all lights to scene.
  _shaders[0]->SetDirectionalLight(mainLight.get());
  _shaders[0]->SetPointLights(pointLights, 3, 0); // Offset 0.
  _shaders[0]->SetSpotLights(spotLights, 3 + pointLightCount, pointLightCount); // Offset by number of point lights.

  _shaders[0]->SetDirectionalLightTransform(&mainLight->CalculateLightTransform());

  // Set main object texture slot to 1.
  _shaders[0]->SetTexture(1);
  // Validate main shader.
  _shaders[0]->Validate();

  for (auto it : activeModels)
  {
    std::shared_ptr<Model> pModel = std::static_pointer_cast<Model>(it.second->GetModel());
    pModel->RenderModel(uniformModel);
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

