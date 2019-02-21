#pragma once

#include <array>
#include <vector>

#include "BaseModule.h"
#include "Scene.h"

// Include submodules
#include "KeyboardManager.h"
#include "MouseManager.h"

using namespace SYE;

struct GLFWwindow;

namespace SYE 
{

class InputManager:
  public BaseModule
{
public:
  // Input processing callbacks
  static void ProcessKeys(GLFWwindow* window, int key, int code, int action, int mode);
  static void ProcessMouseKeys(GLFWwindow* window, int button, int action, int mode);
  static void ProcessMouse(GLFWwindow* window, double xPos, double yPos);


  InputManager() = delete;
  InputManager(BaseModule& parentModule) noexcept;
  ~InputManager() noexcept;
  

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void ProcessScene(dfloat deltaTime, Scene* pScene);

  bool IsKeyboardKeyDown(size_t keyIndex) const;
  bool IsMouseKeyDown(size_t keyIndex) const;
  bool IsOnKeyboardKeyDown(size_t keyIndex) const;
  bool IsOnKeyboardMouseDown(size_t keyIndex) const;
  bool IsOnKeyboardKeyUp(size_t keyIndex) const;
  bool IsOnKeyboardMouseUp(size_t keyIndex) const;

  dfloat GetMouseXPos() const { return _currX; }
  dfloat GetMouseYPos() const { return _currY; }
  dfloat GetMouseXDelta() const { return _deltaX; }
  dfloat GetMouseYDelta() const { return _deltaY; }

private:
  void FlushKeyBuffers();

  // Attributes
public:
  static std::vector<size_t> _keyboardKeysPressed;
  static std::vector<size_t> _mouseKeysPressed;
  static std::array<bool, NUM_KEYBOARD_KEYS> _keyboardKeysDown;
  static std::array<bool, NUM_MOUSE_KEYS> _mouseKeysDown;
  static std::vector<size_t> _keyboardKeysReleased;
  static std::vector<size_t> _mouseKeysReleased;

  static dfloat _currX;
  static dfloat _currY;
  static dfloat _deltaX;
  static dfloat _deltaY;
  static bool _mouseFirstMoved;

};

}