#pragma once

#include <string>

namespace WeSp 
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