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

  Window* ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height);

  void RenderScene(Scene* pScene, Window* pTargetWindow);

  void DirectionalShadowMapPass(Scene* pScene);
  void OmniShadowMapPass(Scene* pScene);
  void FinalMainRenderPass(Scene* pScene);

private:
  void CreateShaders();

  std::vector<std::shared_ptr<Shader>> _shaders;

  bool _perspectiveProjectionMatrixInitialized = false;
  glm::mat4 _perspectiveProjectionMatrix;

  bool _orthoProjectionMatrixInitialized = false;
  glm::mat4 _orthoProjectionMatrix;

  GLuint uf_bIsSkeletonAnimated = 0;
  GLuint uniformProjection = 0;
  GLuint ul_model = 0;
  GLuint uniformView = 0;
  GLuint uniformSpecularIntensity = 0;
  GLuint uniformShininess = 0;
  GLuint uniformEyePosition = 0;
  GLuint uniformOmniLightPos = 0;
  GLuint uniformFarPlane = 0;


#if !NEW_SSSEC_IMPLEMENTED

  void _DirectionalShadowMapPass
  (
    const std::unordered_map<size_t, Entity*>& activeModels,
    const std::unordered_map<size_t, Entity*>& directionalLights
  );
  void _OmniShadowMapPass
  (
    const std::unordered_map<size_t, Entity*>& activeModels,
    const std::unordered_map<size_t, Entity*>& pointLights,
    const std::unordered_map<size_t, Entity*>& spotLights
  );

  void _FinalMainRenderPass
  (
    Scene* pScene, 
    const std::unordered_map<size_t, Entity*>& activeModels,
    const std::unordered_map<size_t, Entity*>& directonalLights,
    const std::unordered_map<size_t, Entity*>& pointLights,
    const std::unordered_map<size_t, Entity*>& spotLights
  );


#endif
};

}
