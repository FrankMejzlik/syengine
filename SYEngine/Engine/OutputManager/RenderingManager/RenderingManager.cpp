#include "RenderingManager.h"

#include "Light_.h"
#include "PointLight_.h"
#include "DirectionalLight_.h"
#include "SpotLight_.h"
#include "MeshRenderer.h"

using namespace SYE;

RenderingManager::RenderingManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Add submodules for this module.
  _subModules.insert(std::make_pair(ID_WINDOW_MANAGER, std::make_unique<WindowManager>(*this)));
  _subModules.insert(std::make_pair(ID_SHADOW_MANAGER, std::make_unique<ShadowManager>(*this)));
  
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
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  

  //

  SetModuleState(eModuleState::OK);
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

Window* RenderingManager::ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height)
{
  // Create new Window instance.
  Window* pNewWindow = WINDOW_MANAGER->ConstructWindow(windowType, windowTitle, width, height);

  // Create and compile shaders.
  CreateShaders();

  // Initialize ImGUI.
  UI_MANAGER->InitializeImGui(pNewWindow);

  return pNewWindow;
}

void RenderingManager::RenderScene(Scene* pScene, Window* pTargetWindow)
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

#if !NEW_SSSEC_IMPLEMENTED

//  // Calculate directional light shadow maps
//  _DirectionalShadowMapPass(pScene->GetActiveModelsRefConst(), pScene->GetDirectionalLightsMapRefConst());
//
//  // Calculat e point light shadow maps
//#if !DISABLE_OMNI_SHADOW_MAPPING
//  _OmniShadowMapPass(pScene->GetActiveModelsRefConst(), pScene->GetPointLightsMapRefConst(), pScene->GetSpotLightsMapRefConst());
//#endif
//  
//
//  // Initialize ImGUI draw.
//  UI_MANAGER->InitializeImGuiDraw();
//
//  // Render actual scene with computed shadow maps
//  _FinalMainRenderPass
//  (
//    pScene,  
//    pScene->GetActiveModelsRefConst(), 
//    pScene->GetDirectionalLightsMapRefConst(), 
//    pScene->GetPointLightsMapRefConst(), 
//    pScene->GetSpotLightsMapRefConst()
//  );
//
#endif

  // Calculate directional light shadow maps
  DirectionalShadowMapPass(pScene);

  // Calculat e point light shadow maps
#if !DISABLE_OMNI_SHADOW_MAPPING
  OmniShadowMapPass(pScene);
#endif

  // Initialize ImGUI draw.
  UI_MANAGER->InitializeImGuiDraw();

  // Render actual scene with computed shadow maps
  FinalMainRenderPass(pScene);

  // Run ImGUI draw.
  //UI_MANAGER->DrawImGui();

  // Swap buffers
  pTargetWindow->SwapBuffers();

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

  std::shared_ptr<Shader> pMainShader = std::make_shared<Shader>(nullptr, _subModules);
  pMainShader->CreateFromFiles(vShader, fShader);
  _shaders.push_back(pMainShader);

  std::shared_ptr<Shader> pDLShader = std::make_shared<Shader>(nullptr, _subModules);
  pDLShader->CreateFromFiles(vDLShader, fDLShader);
  _shaders.push_back(pDLShader);

  std::shared_ptr<Shader> pODLShader = std::make_shared<Shader>(nullptr, _subModules);
  pODLShader->CreateFromFiles(vODLShader, gODLShader, fODLShader);
  _shaders.push_back(pODLShader);

}


void RenderingManager::DirectionalShadowMapPass(Scene* pScene)
{
  // TODO: Implement in Material
  _shaders[1]->UseShader();

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActiveComponentsBySlotsRef();

  for (auto&& dirLight : components[COMPONENT_DIRECTIONAL_LIGHT_SOURCE_SLOT])
  {
    DirectionalLight* light = static_cast<DirectionalLight*>(dirLight.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    GLuint ul_model_ = _shaders[1]->GetModelLocation();
    GLuint ul_specularIntensity_ = _shaders[1]->GetSpecularIntensityLocation();
    GLuint ul_shininess_ = _shaders[1]->GetShininessLocation();


    // Give it correctly calculated lightTransform matrix
    auto lightTransform = light->CalculateLightTransformMatrix();
    _shaders[1]->SetDirectionalLightTransform(&lightTransform);

    //_shaders[1]->Validate();
    // Render objects in scene with their own shaders

    for (auto modelPair : components[COMPONENT_MESH_RENDERER_SLOT])
    {
      MeshRenderer* mashRenderer = static_cast<MeshRenderer*>(modelPair.second);

      mashRenderer->Render(ul_model_, ul_specularIntensity_, ul_shininess_);
    }
  }

  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void RenderingManager::OmniShadowMapPass(Scene* pScene)
{
  // TODO: Implement in Material
  _shaders[2]->UseShader();

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActiveComponentsBySlotsRef();

  for (auto&& pointLight : components[COMPONENT_POINT_LIGHT_SOURCE_SLOT])
  {
    PointLight* light = static_cast<PointLight*>(pointLight.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    GLuint uniformOmniLightPosx = _shaders[2]->GetOmniLightPosLocation();
    GLuint uniformFarPlanex = _shaders[2]->GetFarPlaneLocation();
    GLuint ul_modelx = _shaders[2]->GetModelLocation();
    GLuint ul_specularIntensityx = _shaders[2]->GetSpecularIntensityLocation();
    GLuint ul_shininessx = _shaders[2]->GetShininessLocation();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPosx, light->GetPosition().GetX(), light->GetPosition().GetY(), light->GetPosition().GetZ());
    glUniform1f(uniformFarPlanex, light->GetFarPlane());

    // Bind to shader 6 direction transofrm light metrices
    _shaders[2]->SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    //_shaders[1]->Validate();
    // Render objects in scene with their own shaders

    for (auto modelPair : components[COMPONENT_MESH_RENDERER_SLOT])
    {
      MeshRenderer* mashRenderer = static_cast<MeshRenderer*>(modelPair.second);

      mashRenderer->Render(ul_modelx, ul_specularIntensityx, ul_shininessx);
    }
  }

  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  for (auto&& spotLight : components[COMPONENT_SPOT_LIGHT_SOURCE_SLOT])
  {
    SpotLight* light = static_cast<SpotLight*>(spotLight.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    GLuint uniformOmniLightPosx = _shaders[2]->GetOmniLightPosLocation();
    GLuint uniformFarPlanex = _shaders[2]->GetFarPlaneLocation();
    GLuint ul_modelx = _shaders[2]->GetModelLocation();
    GLuint ul_specularIntensityx = _shaders[2]->GetSpecularIntensityLocation();
    GLuint ul_shininessx = _shaders[2]->GetShininessLocation();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPosx, light->GetPosition().GetX(), light->GetPosition().GetY(), light->GetPosition().GetZ());
    glUniform1f(uniformFarPlanex, light->GetFarPlane());

    // Bind to shader 6 direction transofrm light metrices
    _shaders[2]->SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    //_shaders[1]->Validate();
    // Render objects in scene with their own shaders

    for (auto modelPair : components[COMPONENT_MESH_RENDERER_SLOT])
    {
      MeshRenderer* mashRenderer = static_cast<MeshRenderer*>(modelPair.second);

      mashRenderer->Render(ul_modelx, ul_specularIntensityx, ul_shininessx);
    }
  }

  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderingManager::FinalMainRenderPass(Scene* pScene)
{
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActiveComponentsBySlotsRef();
  
  DirectionalLight* mainLight;
  if (!components[COMPONENT_DIRECTIONAL_LIGHT_SOURCE_SLOT].empty())
  {
    mainLight = static_cast<DirectionalLight*>(components[COMPONENT_DIRECTIONAL_LIGHT_SOURCE_SLOT].begin()->second);
  }
  else
  {
    mainLight = nullptr;
  }
  

  // Set correct viewport, just to be sure
  glViewport(0, 0, GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);

  // Clear window
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw main scene
  _shaders[0]->UseShader();
  uniformProjection = _shaders[0]->GetProjectionLocation();
  uniformView = _shaders[0]->GetViewLocation();
  uniformEyePosition = _shaders[0]->GetEyePosition();
  ul_model = _shaders[0]->GetModelLocation();
  GLuint ul_specularIntensity = _shaders[0]->GetSpecularIntensityLocation();
  GLuint ul_shininess = _shaders[0]->GetShininessLocation();


  // Set values in shader uniforms
  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(_perspectiveProjectionMatrix));
  glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(pScene->GetEditorCamera()->CalculateViewMatrix()));
  glUniform3f(uniformEyePosition, 
    pScene->GetEditorCamera()->GetCameraPosition().x, 
    pScene->GetEditorCamera()->GetCameraPosition().y, 
    pScene->GetEditorCamera()->GetCameraPosition().z
  );

  // Get counts of lights.
  size_t pointLightCount = components[COMPONENT_POINT_LIGHT_SOURCE_SLOT].size();
  size_t spotLightCount = components[COMPONENT_SPOT_LIGHT_SOURCE_SLOT].size(); spotLightCount;


  // Set up all lights to scene.
  if (mainLight)
  {
    _shaders[0]->SetDirectionalLight(mainLight);
  }
  _shaders[0]->SetPointLights(components[COMPONENT_POINT_LIGHT_SOURCE_SLOT], 3, 0ULL); // Offset 0.
  _shaders[0]->SetSpotLights(components[COMPONENT_SPOT_LIGHT_SOURCE_SLOT], 3 + pointLightCount, pointLightCount); // Offset by number of point lights.
  if (mainLight)
  {
    auto lightTranforms = mainLight->CalculateLightTransformMatrix();
    _shaders[0]->SetDirectionalLightTransform(&lightTranforms);
  }

  // Set main object texture slot to 1.
  _shaders[0]->SetTexture(1);
  // Validate main shader.
  //_shaders[0]->Validate();

  for (auto modelPair : components[COMPONENT_MESH_RENDERER_SLOT])
  {
    MeshRenderer* mashRenderer = static_cast<MeshRenderer*>(modelPair.second);

    mashRenderer->Render(ul_model, ul_specularIntensity, ul_shininess);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}





#if !NEW_SSSEC_IMPLEMENTED

void RenderingManager::_DirectionalShadowMapPass
(
  const std::unordered_map<size_t, Entity*>& activeModels, 
  const std::unordered_map<size_t, Entity*>& directionalLights
)
{
  _shaders[1]->UseShader();

  for (auto it : directionalLights)
  {
    _DirectionalLight* light = static_cast<_DirectionalLight*>(it.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    ul_model = _shaders[1]->GetModelLocation();


    // Give it correctly calculated lightTransform matrix
    auto lightTransform = light->CalculateLightTransform();
    _shaders[1]->SetDirectionalLightTransform(&lightTransform);

    //_shaders[1]->Validate();
    // Render objects in scene with their own shaders

    for (auto modelPair : activeModels)
    {
      Model* model;
      model = static_cast<Model*>(modelPair.second->GetModel());
      model->RenderModel(ul_model, modelPair.second);

    }
  }

  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void RenderingManager::_OmniShadowMapPass
(
  const std::unordered_map<size_t, Entity*>& activeModels, 
  const std::unordered_map<size_t, Entity*>& pointLights,
  const std::unordered_map<size_t, Entity*>& spotLights
)
{


  _shaders[2]->UseShader();

  // Process PointLights.
  for (auto it : pointLights)
  {
    _PointLight* light = static_cast<_PointLight*>(it.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    ul_model = _shaders[2]->GetModelLocation();
    uniformOmniLightPos = _shaders[2]->GetOmniLightPosLocation();
    uniformFarPlane = _shaders[2]->GetFarPlaneLocation();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
    glUniform1f(uniformFarPlane, light->GetFarPlane());

    // Bind to shader 6 direction transofrm light metrices
    _shaders[2]->SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    //_shaders[2]->Validate();

    // Render objects in scene with their own shaders

    for (auto modelPair : activeModels)
    {
      Model* model = static_cast<Model*>(modelPair.second->GetModel());
      model->RenderModel(ul_model, modelPair.second);

    }
  }

  // Process SpotLights.
  for (auto it : spotLights)
  {
    _SpotLight* light = static_cast<_SpotLight*>(it.second);

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    ul_model = _shaders[2]->GetModelLocation();
    uniformOmniLightPos = _shaders[2]->GetOmniLightPosLocation();
    uniformFarPlane = _shaders[2]->GetFarPlaneLocation();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
    glUniform1f(uniformFarPlane, light->GetFarPlane());

    // Bind to shader 6 direction transofrm light metrices
    _shaders[2]->SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    //_shaders[2]->Validate();

    // Render objects in scene with their own shaders

    for (auto modelPair : activeModels)
    {
      Model* model;
      model = static_cast<Model*>(modelPair.second->GetModel());
      model->RenderModel(ul_model, modelPair.second);

    }
  }


  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderingManager::_FinalMainRenderPass
(
  Scene* pScene, 
  const std::unordered_map<size_t, Entity*>& activeModels, 
  const std::unordered_map<size_t, Entity*>& directionalLights,
  const std::unordered_map<size_t, Entity*>& pointLights,
  const std::unordered_map<size_t, Entity*>& spotLights
)
{
  _DirectionalLight* mainLight = static_cast<_DirectionalLight*>(directionalLights.begin()->second);

  // Set correct viewport, just to be sure
  glViewport(0, 0, GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);

  // Clear window
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw main scene
  _shaders[0]->UseShader();
  ul_model = _shaders[0]->GetModelLocation();
  uniformProjection = _shaders[0]->GetProjectionLocation();
  uniformView = _shaders[0]->GetViewLocation();
  uniformEyePosition = _shaders[0]->GetEyePosition();


  // Set values in shader uniforms
  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(_perspectiveProjectionMatrix));
  glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(pScene->GetEditorCamera()->CalculateViewMatrix()));
  glUniform3f(uniformEyePosition, 
    pScene->GetEditorCamera()->GetCameraPosition().x, 
    pScene->GetEditorCamera()->GetCameraPosition().y, 
    pScene->GetEditorCamera()->GetCameraPosition().z
  );

  // Get counts of lights.
  size_t pointLightCount = pointLights.size();
  size_t spotLightCount = spotLights.size(); spotLightCount;


  // Set up all lights to scene.
  _shaders[0]->_SetDirectionalLight(mainLight);
  _shaders[0]->_SetPointLights(pointLights, 3, 0ULL); // Offset 0.
  _shaders[0]->_SetSpotLights(spotLights, 3 + pointLightCount, pointLightCount); // Offset by number of point lights.

  auto lightTranforms = mainLight->CalculateLightTransform();
  _shaders[0]->SetDirectionalLightTransform(&lightTranforms);

  // Set main object texture slot to 1.
  _shaders[0]->SetTexture(1);
  // Validate main shader.
  //_shaders[0]->Validate();

  for (auto it : activeModels)
  {
    Model* pModel = (Model*)it.second->GetModel();
    pModel->RenderModel(ul_model, pModel->GetOwnerEntityPtr());
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#endif