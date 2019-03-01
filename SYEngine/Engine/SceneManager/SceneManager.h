#pragma once

#include <assert.h>

#include <map>
#include <string>
#include <string_view>

#include "common.h"
#include "BaseModule.h"
#include "Scene.h"
#include "ComponentManager.h"
#include "EntityManager.h"

using namespace SYE;

namespace SYE 
{

class Engine;

class SceneManager :
  public BaseModule
{
  // Methods.
public:
  static Scene* GetActiveScene();
  
  SceneManager() = delete;
  SceneManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~SceneManager() noexcept;
  
  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool InitializeScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);

  /**
   * Gets Scene instance by its name if exists. Else returns nullptr.
   */
  const Scene* GetSceneConstPtr(size_t sceneGuid) const;
  Scene* GetScenePtr(size_t sceneGuid);
  Scene* InsertScene(std::unique_ptr<Scene>&& sceneToInsert);

  Scene* CreateScene(EngineContext* pEngineContext, Engine* pOwnerEngine, Window* pWindow, size_t sceneId);
  Scene* LoadInitialScene(Scene* pNewScene);
  void HandleInput(Scene* pScene);

  // Attributes.
private:
  /** Currently active scene */
  static Scene* _pActiveScene;

  /** Instantiated scenes hashed by GUID. */
  std::map< size_t, std::unique_ptr<Scene> > _scenes;

protected:
public:
};

} // namespace SYE