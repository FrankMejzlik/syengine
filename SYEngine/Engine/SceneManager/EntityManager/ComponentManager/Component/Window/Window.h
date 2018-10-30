#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "config_engine.h"

#include "Component.h"

namespace SYE 
{

class Window:
  public Component
{
public:
  Window() = delete;

  Window(std::shared_ptr<Entity> pEntity, GLsizei windowWidth, GLsizei WindowHeight);
  ~Window();

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
  
  GLFWwindow* GetPGlfwWindow() const { return mainWindow; }

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