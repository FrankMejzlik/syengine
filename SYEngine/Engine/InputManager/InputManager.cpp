#include "InputManager.h"

InputManager::InputManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_KEYBOARD_MANAGER, std::make_shared<KeyboardManager>(*this)));
  _subModules.insert(std::make_pair(ID_MOUSE_MANAGER, std::make_shared<MouseManager>(*this)));
  

  DLog(eLogType::Success, "InputManager instance created.");
}

InputManager::~InputManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "InputManager instance destroyed.");
}

void InputManager::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
  Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

  // Handle pushdowns and pushups
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key == GLFW_KEY_T && action == GLFW_PRESS)
  {
    theWindow->ShowCursor();
  }

  if (key == GLFW_KEY_G && action == GLFW_PRESS)
  {
    theWindow->HideCursor();
  }

  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
    {
      theWindow->keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
      theWindow->keys[key] = false;
    }
  }
}

void InputManager::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
  Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (theWindow->_bMoveOnMouseMove)
  {

    if (theWindow->mouseFirstMoved)
    {
      theWindow->lastX = static_cast<GLfloat>(xPos);
      theWindow->lastY = static_cast<GLfloat>(yPos);
      theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = static_cast<GLfloat>(xPos - theWindow->lastX);
    theWindow->yChange = static_cast<GLfloat>(theWindow->lastY - yPos);

    theWindow->lastX = static_cast<GLfloat>(xPos);
    theWindow->lastY = static_cast<GLfloat>(yPos);
  }
  //printf("x: %.f6f, y: %.6f\n", theWindow->xChange, theWindow->yChange);
}


bool InputManager::Initialize()
{

  // Class specific initialization
  // -- Goes here
  // Class specific initialization

  // Initialize submodules.
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "InputManager instance initialized.");
  return true;
}

bool InputManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "InputManager instance terminated.");
  return true;
}

void InputManager::ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene)
{



}
