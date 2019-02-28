#pragma once

#include <memory>

#include "common.h"
#include "BaseModule.h"

namespace SYE 
{

// Forward declarations
class PhysicsScene;
class Scene;
class PhysicsDebugRenderer;

class PhysicsManager :
  public BaseModule
{
public:
  PhysicsManager() = delete;
  PhysicsManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~PhysicsManager() noexcept;

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool InitializeScene(Scene* pScene);
  void TerminateScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);

  PhysicsDebugRenderer* GetDebugRendererPtr() const;

private:
  /**
   * Owning pointer to current physics scene.
   *
   * TODO: Implement multiple physics scenes support.
   */
  std::unique_ptr<PhysicsScene> _pPhysicsScene;
};

}