#pragma once

#include <memory>

#include "common.h"
#include "BaseModule.h"

namespace SYE 
{

// Forward declarations
class PhysicsScene;
class Scene;

class PhysicsManager :
  public BaseModule
{
public:
  PhysicsManager() = delete;
  PhysicsManager(BaseModule &parentModule) noexcept;
  ~PhysicsManager() noexcept;

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void InitializePhysicsScene(Scene* pScene);
  void TerminatePhysicsScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);


private:
  /**
   * Owning pointer to current physics scene.
   *
   * TODO: Implement multiple physics scenes support.
   */
  std::unique_ptr<PhysicsScene> _pPhysicsScene;
};

}