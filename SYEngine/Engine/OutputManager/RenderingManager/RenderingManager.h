#pragma once

#include <memory>

#include "common.h"
#include "BaseModule.h"
#include "ShaderManager.h"
#include "UiManager.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Scene.h"

// Submodules.
#include "WindowManager.h"

using namespace SYE;

namespace SYE 
{

class PhysicsDebugRenderer;
class Mesh;
class Entity;


class RenderingManager :
  public BaseModule
{
public:
  static void OpenGlErrorCallack(int error, const char* description);

  RenderingManager() = delete;

  RenderingManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~RenderingManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool InitializeGraphicsApi();
  bool InitializeScene(Scene* pScene);

  void TogglePhysicsDrawWireframe();
  void TogglePhysicsDrawAABBs();

  Window* ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height);
  bool DestroyWindow(Window* pWindow);

  void RenderScene(Scene* pScene, Window* pTargetWindow);

#if !NEW_SHADOW_MAPPING_IMPLEMENTED
  void dc_DirectionalShadowMapPass(Scene* pScene);
  void dc_OmniShadowMapPass(Scene* pScene);
#endif

  void DirectionalLightShadowMapPass(Scene* pScene);

  void FinalMainRenderPass(Scene* pScene);

  PhysicsDebugRenderer* GetPhysicsDebugRendererPtr() const { return _pPhysicsDebugRenderer.get(); }

private:
  void CreateShaders();


  // Attributes
private:
  std::vector< std::unique_ptr<Shader> > _shaders;

  GLuint uf_bIsSkeletonAnimated = 0;
  GLuint uniformProjection = 0;
  GLuint ul_model = 0;
  GLuint uniformView = 0;
  GLuint uniformSpecularIntensity = 0;
  GLuint uniformShininess = 0;
  GLuint uniformEyePosition = 0;
  GLuint uniformOmniLightPos = 0;
  GLuint uniformFarPlane = 0;

  std::unique_ptr<PhysicsDebugRenderer> _pPhysicsDebugRenderer;
 
};

}
