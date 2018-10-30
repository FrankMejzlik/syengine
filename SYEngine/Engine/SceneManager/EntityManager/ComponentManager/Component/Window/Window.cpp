
#include "windows.h"

#include "Window.h"

#include "EngineContext.h"

using namespace SYE;

Window::Window(std::shared_ptr<Entity> pEntity, GLsizei windowWidth = 800, GLsizei windowHeight = 600) :
  Component(pEntity),
  bufferWidth(windowWidth), bufferHeight(windowHeight), xChange(0.0f), yChange(0.0f), mouseFirstMoved(true)
{
  for (size_t i = 0; i < 1024; ++i)
  {
    keys[i] = 0;
  }
}

int Window::Initialize()
{
  // Initialize GLFW
  if (!glfwInit())
  {
    printf("GLFW init failed!\n");
    glfwTerminate();
    return 1;
  }

  // Setup GLFW window properties
  // OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Core profile = No backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Allow forward compatiblity
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  mainWindow = glfwCreateWindow(bufferWidth, bufferHeight, GAME_WINDOW_TITLE, NULL, NULL);
  if (!mainWindow)
  {
    printf("GLFW window creation failed!\n");
    glfwTerminate();
    return 2;
  }
  // Set window position
  glfwSetWindowPos(mainWindow, GAME_WINDOW_DEFAULT_POS_X, GAME_WINDOW_DEFAULT_POS_Y);

  // Set context for GLEW to use
  glfwMakeContextCurrent(mainWindow);

  // Handle key + mouse
  CreateCallbacks();
  glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Alow moder extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    printf("GLEW init failed!\n");
    glfwDestroyWindow(mainWindow);
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
  // Setup viewport size
  glViewport(0, 0, bufferWidth, bufferHeight);

  // Set instance that belongs to winwow
  glfwSetWindowUserPointer(mainWindow, this);

  printf("Engine initialzied...\n");
  return 0;
}

Window::~Window()
{
  glfwTerminate();
}


void Window::CreateCallbacks()
{
  // When key is pressed in main window call HhadleKeys
  glfwSetKeyCallback(mainWindow, InputManager::HandleKeys);
  glfwSetMouseButtonCallback(mainWindow, InputManager::HandleMouseKeys);
  glfwSetCursorPosCallback(mainWindow, InputManager::HandleMouse);
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
