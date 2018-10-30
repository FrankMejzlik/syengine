#pragma once

#include <string>

namespace SYE 
{

class SceneContext
{
public:
  SceneContext();

  SceneContext(std::string sceneName);
   
  ~SceneContext();
  
  std::string m_sceneName;
};

}