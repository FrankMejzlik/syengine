#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "common.h"
#include "InputManager.h"

#include "Component.h"

namespace SYE 
{

class Window
{
  friend class InputManager;

public:
  


  Window() = delete;

  Window(GLsizei windowWidth, GLsizei WindowHeight);
  ~Window();

  int Initialize();

  void ShowCursor() { 
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    _bMoveOnMouseMove = false;
  }
  void HideCursor() {
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    _bMoveOnMouseMove = true;
  };

  GLsizei GetBufferWidth()
  {
    return bufferWidth;
  }

  GLsizei GetBufferHeight()
  {
    return bufferHeight;
  }

  bool GetShouldClose()
  {
    return glfwWindowShouldClose(mainWindow);
  }

  bool* GetKeys() { return keys; }
  bool* GetMouseKeys() { return _mouseKeys; }

  GLfloat GetXChange();
  GLfloat GetYChange();

  void SwapBuffers()
  {
    glfwSwapBuffers(mainWindow);
  }
  
  GLFWwindow* GetPGlfwWindow() const { return mainWindow; }
 
  bool _bMoveOnMouseMove = true;
private:
  
  GLFWwindow* mainWindow;
  GLsizei bufferWidth, bufferHeight;
  bool keys[1024];
  bool _mouseKeys[1024];
  GLfloat lastX;
  GLfloat lastY;
  GLfloat xChange;
  GLfloat yChange;
  bool mouseFirstMoved;


  //static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
  //static void HandleMouse(GLFWwindow* window, double xPos, double yPos);

  void CreateCallbacks();

};

}