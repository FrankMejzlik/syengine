
#include "InputManager.h"

#include "Window.h"

// Statics
std::vector<size_t> InputManager::_keyboardKeysPressed = std::vector<size_t>();
std::vector<size_t> InputManager::_mouseKeysPressed = std::vector<size_t>();
std::array<bool, NUM_KEYBOARD_KEYS> InputManager::_keyboardKeysDown = std::array<bool, NUM_KEYBOARD_KEYS>();
std::array<bool, NUM_MOUSE_KEYS> InputManager::_mouseKeysDown = std::array<bool, NUM_MOUSE_KEYS>();
std::vector<size_t> InputManager::_keyboardKeysReleased = std::vector<size_t>();
std::vector<size_t> InputManager::_mouseKeysReleased = std::vector<size_t>();

int InputManager::_currX = 0;
int InputManager::_currY = 0;
int InputManager::_deltaX = 0;
int InputManager::_deltaY = 0;
bool InputManager::_mouseFirstMoved = false;

InputManager::InputManager(BaseModule &parentModule) noexcept:
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_KEYBOARD_MANAGER, std::make_unique<KeyboardManager>(*this)));
  _subModules.insert(std::make_pair(ID_MOUSE_MANAGER, std::make_unique<MouseManager>(*this)));
  

  DLog(eLogType::Success, "InputManager instance created.");
}

InputManager::~InputManager() noexcept
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "InputManager instance destroyed.");
}

void InputManager::ProcessKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
  UNREFERENCED_PARAMETER(window);
  UNREFERENCED_PARAMETER(mode);
  UNREFERENCED_PARAMETER(code);


  Window* pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));


  // Handle pushdowns and pushups
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key == GLFW_KEY_T && action == GLFW_PRESS)
  {
    pWindow->ShowCursor();
  }

  if (key == GLFW_KEY_G && action == GLFW_PRESS)
  {
    pWindow->HideCursor();
  }

  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
    {

      // Set this key to not pressed
      _keyboardKeysDown[key] = true;
      // Set it as this frame PRESSED key
      _keyboardKeysPressed.push_back(key);
    }
    else if (action == GLFW_RELEASE)
    {
      // Set this key to not pressed
      _keyboardKeysDown[key] = false;
      // Set it as this frame RELEASE key
      _keyboardKeysReleased.push_back(key);
    }
  }
}

void InputManager::ProcessMouseKeys(GLFWwindow* window, int button, int action, int mode)
{
  UNREFERENCED_PARAMETER(window);
  UNREFERENCED_PARAMETER(mode);
  UNREFERENCED_PARAMETER(action);


  Window* pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
  pWindow;


  if (button >= 0 && button < 1024)
  {
    if (action == GLFW_PRESS)
    {
      // Set this key to not pressed
      _mouseKeysDown[button] = true;
      // Set it as this frame PRESSED key
      _mouseKeysPressed.push_back(button);
    }
    else if (action == GLFW_RELEASE)
    {
       // Set this key to not pressed
      _mouseKeysDown[button] = false;
      // Set it as this frame RELEASE key
      _mouseKeysReleased.push_back(button);
    }
  }
}

void InputManager::ProcessMouse(GLFWwindow* window, double xPos, double yPos)
{
  UNREFERENCED_PARAMETER(window);

  // If this is first mouse movement
  if (!_mouseFirstMoved)
  {
    // To prevent first move look jump
    _currX = static_cast<int>(xPos);
    _currY = static_cast<int>(yPos);
    _mouseFirstMoved = true;
  }

  _deltaX = static_cast<int>(xPos - _currX);
  _deltaY = static_cast<int>(_currY - yPos);

  _currX = static_cast<int>(xPos);
  _currY = static_cast<int>(yPos);

  }

bool InputManager::Initialize()
{

  // Class specific initialization
  // -- Goes here
  // Class specific initialization

  // Initialize submodules.
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  SetModuleState(eModuleState::OK);
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

void InputManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{
  UNREFERENCED_PARAMETER(deltaTime);
  UNREFERENCED_PARAMETER(pScene);

  _deltaX = 0ULL;
  _deltaY = 0ULL;

  // Clear all key buffers before processing this frame's input
  FlushKeyBuffers();

  /*
    Process all pending events

    This calls all registered input callbacks.
  */
  glfwPollEvents();
  
}


bool InputManager::IsKeyboardKeyDown(size_t keyIndex) const
{
  // Check if is out of bound
  if (keyIndex < 0 && keyIndex >= NUM_KEYBOARD_KEYS)
  {
    return false;
  }

  return _keyboardKeysDown[keyIndex];
}

bool InputManager::IsMouseKeyDown(size_t keyIndex) const
{
  // Check if is out of bound
  if (keyIndex < 0 && keyIndex >= NUM_MOUSE_KEYS)
  {
    return false;
  }

  return _mouseKeysDown[keyIndex];
}

bool InputManager::IsOnKeyboardKeyDown(size_t keyIndex) const
{
  // Iterate through this frame pressed keys
  for (auto&& keyCode : _keyboardKeysPressed)
  {
    if (keyCode == keyIndex)
    {
      return true;
    }
  }

  return false;
}

bool InputManager::IsOnKeyboardMouseDown(size_t keyIndex) const
{
  // Iterate through this frame pressed mouse keys
  for (auto&& keyCode : _mouseKeysPressed)
  {
    if (keyCode == keyIndex)
    {
      return true;
    }
  }

  return false;
}

bool InputManager::IsOnKeyboardKeyUp(size_t keyIndex) const
{
  // Iterate through this frame released keys
  for (auto&& keyCode : _keyboardKeysReleased)
  {
    if (keyCode == keyIndex)
    {
      return true;
    }
  }

  return false;
}
bool InputManager::IsOnKeyboardMouseUp(size_t keyIndex) const
{
  // Iterate through this frame released keys
  for (auto&& keyCode : _mouseKeysReleased)
  {
    if (keyCode == keyIndex)
    {
      return true;
    }
  }

  return false;
}

void InputManager::FlushKeyBuffers()
{
  // Reset all of them
  _keyboardKeysPressed.clear();
  _mouseKeysPressed.clear();
  _keyboardKeysReleased.clear();
  _mouseKeysReleased.clear();
}