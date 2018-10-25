#pragma once

#include <map>
#include <string>


#include "common.h"
#include "BaseModule.h"
#include "Scene.h"

using namespace WeSp;

namespace WeSp 
{

class SceneManager :
  public BaseModule
{
public:
  SceneManager() = delete;

  SceneManager(BaseModule &parentModule);
  ~SceneManager();

  /**
   * Gets Scene instance by its name if exists. Else returns nullptr.
   */
  std::shared_ptr<Scene> GetScene(std::string sceneName);
  std::shared_ptr<Scene> CreateScene(std::string sceneName);
  std::shared_ptr<Scene> LoadInitialScene();

  
  
  virtual bool Initialize() override;
  virtual bool Terminate() override;

private:
  std::map<std::string, std::shared_ptr<Scene>> _scenes;

};

} // namespace WeSp