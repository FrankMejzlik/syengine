#pragma once

#include <string>
#include <vector>

#include "Entity.h"
#include "SceneContext.h"

namespace WeSp
{

class Scene
{
public:
  Scene() = delete;

  Scene(std::string sceneName);
  ~Scene();

  std::string GetSceneName();


private:
  SceneContext _sceneContext;
  std::vector<Entity> _entities;

};

} // namespace WeSp