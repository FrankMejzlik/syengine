#pragma once

#include "common.h"
#include "BaseModule.h"
#include "ShaderManager.h"
#include "ShadowManager.h"
#include "UiManager.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Scene.h"

// Submodules.
#include "WindowManager.h"

using namespace SYE;

namespace SYE 
{

class RenderingManager :
  public BaseModule
{
public:
  RenderingManager() = delete;

  RenderingManager(BaseModule &parentModule);
  ~RenderingManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::shared_ptr<Window> ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height);

  void RenderScene(std::shared_ptr<Scene> pScene, std::shared_ptr<Window> pTargetWindow);

private:
  void CreateShaders();

  std::vector<std::shared_ptr<Shader>> _shaders;

  bool _perspectiveProjectionMatrixInitialized = false;
  glm::mat4 _perspectiveProjectionMatrix;

  bool _orthoProjectionMatrixInitialized = false;
  glm::mat4 _orthoProjectionMatrix;

  GLuint uf_bIsSkeletonAnimated = 0;
  GLuint uniformProjection = 0;
  GLuint uniformModel = 0;
  GLuint uniformView = 0;
  GLuint uniformSpecularIntensity = 0;
  GLuint uniformShininess = 0;
  GLuint uniformEyePosition = 0;
  GLuint uniformOmniLightPos = 0;
  GLuint uniformFarPlane = 0;

  void DirectionalShadowMapPass
  (
    const std::unordered_map<size_t, Entity*>& activeModels,
    const std::unordered_map<size_t, Entity*>& directionalLights
  );
  void OmniShadowMapPass
  (
    const std::unordered_map<size_t, Entity*>& activeModels,
    const std::unordered_map<size_t, Entity*>& pointLights,
    const std::unordered_map<size_t, Entity*>& spotLights
  );

  void FinalMainRenderPass
  (
    std::shared_ptr<Scene> pScene, 
    const std::unordered_map<size_t, Entity*>& activeModels,
    const std::unordered_map<size_t, Entity*>& directonalLights,
    const std::unordered_map<size_t, Entity*>& pointLights,
    const std::unordered_map<size_t, Entity*>& spotLights
  );



};

}
