#include "SceneContext.h"

using namespace SYE;


SceneContext::SceneContext(size_t sceneId):
  _sceneId(sceneId)
{}

size_t SceneContext::GetSceneId() const
{
  return _sceneId;
}