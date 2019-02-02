#pragma once


#include "BaseModule.h"
#include "Scene.h"

// Include submodules
#include "KeyboardManager.h"
#include "MouseManager.h"

using namespace SYE;

namespace SYE {

class InputManager:
  public BaseModule
{
public:
  static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
  static void HandleMouseKeys(GLFWwindow* window, int button, int action, int mode);
  static void HandleMouse(GLFWwindow* window, double xPos, double yPos);


  InputManager() = delete;

  InputManager(BaseModule &parentModule);
  ~InputManager();
  
  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void ProcessScene(dfloat deltaTime, Scene* pScene);

private:

};

}