#include "SceneContext.h"

using namespace SYE;


SceneContext::SceneContext()
{}

SceneContext::SceneContext(std::string_view sceneName):
  m_sceneName(sceneName)
{

}


SceneContext::~SceneContext()
{}
