#pragma once

#include "common.h"

namespace SYE 
{

class SceneContext
{
public:
  SceneContext() = delete;
  SceneContext(size_t sceneId);


  size_t GetSceneId() const;

private:
  /** ID/index of this scene */
  size_t _sceneId;
};

}
