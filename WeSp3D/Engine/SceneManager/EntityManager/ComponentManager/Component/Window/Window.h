#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "config_engine.h"

#include "Component.h"

namespace WeSp 
{

class Window:
  public Component
{
public:
  Window(GLsizei windowWidth, GLsizei WindowHeight);

  int Initialize();

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
  GLfloat GetXChange();
  GLfloat GetYChange();

  void SwapBuffers()
  {
    glfwSwapBuffers(mainWindow);
  }
  
  ~Window();

private:
  GLFWwindow* mainWindow;
  GLsizei bufferWidth, bufferHeight;
  bool keys[1024];
  GLfloat lastX;
  GLfloat lastY;
  GLfloat xChange;
  GLfloat yChange;
  bool mouseFirstMoved;

  static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
  static void HandleMouse(GLFWwindow* window, double xPos, double yPos);

  void CreateCallbacks();

};

}