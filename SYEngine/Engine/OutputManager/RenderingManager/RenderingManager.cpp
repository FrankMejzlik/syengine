#include "RenderingManager.h"

#include <GL/glew.h>

#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "PhysicsDebugRenderer.h"
#include "PhysicsScene.h"

using namespace SYE;


void RenderingManager::OpenGlErrorCallack(int error, const char* description)
{
  DLog(eLogType::Error, "Error %d: %s", error, description);
}

RenderingManager::RenderingManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext),
  _pPhysicsDebugRenderer(std::make_unique<PhysicsDebugRenderer>())
{
  // Add submodules for this module.
  _subModules.insert(std::make_pair(ID_WINDOW_MANAGER, std::make_unique<WindowManager>(*this, _pEngineContext)));
  
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  // Set debug renderer level
  _pPhysicsDebugRenderer->setDebugMode(0);

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

  // Initialize graphics API
  if (!InitializeGraphicsApi())
  {
    PUSH_ENGINE_ERROR(
      eEngineError::GraphicsApiInitializationFailed,
      "Failed to initialize OpenGL (GLFW).",
      ""
    );

    return false;
  }

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


bool RenderingManager::InitializeGraphicsApi()
{
  // Register error callback
  glfwSetErrorCallback(OpenGlErrorCallack);

  // Initialize GLFW
  if (!glfwInit())
  {
    printf("GLFW init failed!\n");
    glfwTerminate();
    return false;
  }

  // Setup GLFW window properties
  // OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Core profile = No backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Allow forward compatiblity
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  


  return true;
}

void RenderingManager::TogglePhysicsDrawWireframe()
{
  // Toggle Wireframe physics debug draw
  _pPhysicsDebugRenderer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
}

void RenderingManager::TogglePhysicsDrawAABBs()
{
  // Toggle AABB draw
  _pPhysicsDebugRenderer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
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

bool RenderingManager::DestroyWindow(Window* pWindow)
{
  return WINDOW_MANAGER->DestroyWindow(pWindow);
}

void RenderingManager::RenderScene(Scene* pScene, Window* pTargetWindow)
{
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

  // Draw debug physics info
  _shaders[3]->UseShader();
  pScene->GetPhysicsScenePtr()->DrawDebug(_shaders[3]->GetShaderID(), pScene->GetEditorCamera()->GetViewMatrixConstRef(), pScene->GetEditorCamera()->GetPerspectiveProjectionMatrixConstRef());

  // Swap buffers
  pTargetWindow->SwapBuffers();

}

void RenderingManager::CreateShaders()
{
  // Line shader for line drawing
  const char* lineVertexShader = "shaders/line_shader.vert";
  const char* lineFragShader = "shaders/line_shader.frag";

  const char* vShader = "shaders/shader.vert";
  const char* fShader = "shaders/shader.frag";
  const char* vDLShader = "shaders/directional_shadow_map.vert";
  const char* fDLShader = "shaders/directional_shadow_map.frag";
  const char* vODLShader = "shaders/omni_shadow_map.vert";
  const char* gODLShader = "shaders/omni_shadow_map.geom";
  const char* fODLShader = "shaders/omni_shadow_map.frag";

  
  // Main shader
  std::unique_ptr<Shader> pMainShader = std::make_unique<Shader>(nullptr, nullptr);
  pMainShader->CreateFromFiles(vShader, fShader);
  _shaders.push_back(std::move(pMainShader));

  // Directional light shader
  std::unique_ptr<Shader> pDLShader = std::make_unique<Shader>(nullptr, nullptr);
  pDLShader->CreateFromFiles(vDLShader, fDLShader);
  _shaders.push_back(std::move(pDLShader));

  // Omnidir light shader
  std::unique_ptr<Shader> pODLShader = std::make_unique<Shader>(nullptr, nullptr);
  pODLShader->CreateFromFiles(vODLShader, gODLShader, fODLShader);
  _shaders.push_back(std::move(pODLShader));

  // Line shader
  std::unique_ptr<Shader> pLineShader = std::make_unique<Shader>(nullptr, nullptr);
  pLineShader->CreateFromFiles(lineVertexShader, lineFragShader);
  _shaders.push_back(std::move(pLineShader));

}


void RenderingManager::DirectionalShadowMapPass(Scene* pScene)
{
  // TODO: Implement in Material
  _shaders[1]->UseShader();

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActivePrimaryComponentSlotsRef();

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

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActivePrimaryComponentSlotsRef();

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

    const Vector3f& pos = light->GetPositionConstRef();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPosx, pos.GetX(), pos.GetY(), pos.GetZ());
    glUniform1f(uniformFarPlanex, light->GetFarPlane());

    // Bind to shader 6 direction transofrm light metrices
    _shaders[2]->SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    //_shaders[1]->Validate();
    // Render objects in scene with their own shaders

    for (auto modelPair : components[COMPONENT_MESH_RENDERER_SLOT])
    {
      MeshRenderer* mashRenderer = static_cast<MeshRenderer*>(modelPair.second);

      mashRenderer->RenderForLight(ul_modelx);
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
    ul_model = _shaders[2]->GetModelLocation();
    uniformOmniLightPos = _shaders[2]->GetOmniLightPosLocation();
    uniformFarPlane = _shaders[2]->GetFarPlaneLocation();

    const Vector3f& pos = light->GetPositionConstRef();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPos, pos.GetX(), pos.GetY(), pos.GetZ());
    glUniform1f(uniformFarPlane, light->GetFarPlane());

    // Bind to shader 6 direction transofrm light metrices
    _shaders[2]->SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    //_shaders[1]->Validate();
    // Render objects in scene with their own shaders

    for (auto modelPair : components[COMPONENT_MESH_RENDERER_SLOT])
    {
      MeshRenderer* mashRenderer = static_cast<MeshRenderer*>(modelPair.second);

      mashRenderer->RenderForLight(ul_model);
    }
  }

  // Deatach from framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderingManager::FinalMainRenderPass(Scene* pScene)
{
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> components = pScene->GetActivePrimaryComponentSlotsRef();
  
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
  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(pScene->GetEditorCamera()->GetPerspectiveProjectionMatrixConstRef()));
  glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(pScene->GetEditorCamera()->GetViewMatrixConstRef()));
  glUniform3f(uniformEyePosition, 
    pScene->GetEditorCamera()->GetCameraPosition().GetX(), 
    pScene->GetEditorCamera()->GetCameraPosition().GetY(), 
    pScene->GetEditorCamera()->GetCameraPosition().GetZ()
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
