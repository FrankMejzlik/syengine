#pragma once

#include <string>

namespace SYE 
{

class SceneContext
{
public:
  SceneContext();

  SceneContext(std::string_view sceneName);
   
  ~SceneContext();
  
  std::string_view m_sceneName;
};

}