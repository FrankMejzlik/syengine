
#include "InputManager.h"

struct GLFWwindow;

IMGUI_IMPL_API bool     ImGuiWrapper_InitForOpenGL(GLFWwindow* window, bool install_callbacks);
IMGUI_IMPL_API bool     ImGuiWrapper_InitForVulkan(GLFWwindow* window, bool install_callbacks);
IMGUI_IMPL_API void     ImGuiWrapper_Shutdown();
IMGUI_IMPL_API void     ImGuiWrapper_NewFrame();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
IMGUI_IMPL_API void     ImGuiWrapper_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
IMGUI_IMPL_API void     ImGuiWrapper_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
IMGUI_IMPL_API void     ImGuiWrapper_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
IMGUI_IMPL_API void     ImGuiWrapper_CharCallback(GLFWwindow* window, unsigned int c);
