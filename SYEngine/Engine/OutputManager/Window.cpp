
#include "windows.h"

#include "Window.h"

#include "EngineContext.h"
#include "Camera.h"

using namespace SYE;

Window::Window(GLsizei windowWidth = 800, GLsizei windowHeight = 600) :
  bufferWidth(windowWidth), bufferHeight(windowHeight), xChange(0.0f), yChange(0.0f), mouseFirstMoved(true)
{
  for (size_t i = 0; i < 1024; ++i)
  {
    keys[i] = 0;
  }
}

int Window::Initialize()
{
  mainWindow = glfwCreateWindow(bufferWidth, bufferHeight, GAME_WINDOW_TITLE, NULL, NULL);
  if (!mainWindow)
  {
    DLog(eLogType::Error, "GLFW window creation failed!");
    glfwTerminate();
    return 2;
  }
  // Set window position
  glfwSetWindowPos(mainWindow, GAME_WINDOW_DEFAULT_POS_X, GAME_WINDOW_DEFAULT_POS_Y);

  // Set context for GLEW to use to this window
  glfwMakeContextCurrent(mainWindow);

  // Alow modern extension features
  glewExperimental = GL_TRUE;

  // Initialize GLEW
  auto glewInitResult = glewInit();
  if (glewInitResult != GLEW_OK)
  {
    DLog(eLogType::Error, "GLEW init failed!");
    glfwTerminate();
    return 3;
  }

  // Depth test
  glEnable(GL_DEPTH_TEST);

#if DISABLE_VSYNC

  // Disable VSync
  glfwSwapInterval(0);

#endif

#if BACK_FACE_CULLING

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

#endif

  // Handle key + mouse
  CreateCallbacks();
  glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Setup viewport size
  glViewport(0, 0, bufferWidth, bufferHeight);

  // Set instance that belongs to winwow
  glfwSetWindowUserPointer(mainWindow, this);

  DLog(eLogType::Success, "Engine initialzied...");

  return 0;
}

Window::~Window()
{
  glfwTerminate();
}


void Window::SetAsRenderTarget(Scene* pScene)
{
  pScene->GetMainCamera()->SetTargetWindow(this);

  // Tell OpenGL to render to window
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  // Setup correct viewport
  glViewport(0, 0, GetBufferWidth(), GetBufferHeight());
}

void Window::CreateCallbacks()
{
  // When key is pressed in main window call HhadleKeys
  glfwSetKeyCallback(mainWindow, InputManager::ProcessKeys);
  glfwSetMouseButtonCallback(mainWindow, InputManager::ProcessMouseKeys);
  glfwSetCursorPosCallback(mainWindow, InputManager::ProcessMouse);
}
GLfloat Window::GetXChange()
{
  GLfloat theChange = xChange;
  xChange = 0.0f;
  return theChange;
}
GLfloat Window::GetYChange()
{
  GLfloat theChange = yChange;
  yChange = 0.0f;
  return theChange;
}
