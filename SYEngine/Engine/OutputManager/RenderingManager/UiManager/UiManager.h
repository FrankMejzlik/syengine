#pragma once

#include <vector>

#include "imgui/imgui.h"

#include "common.h"
#include "BaseModule.h"
#include "Window.h"

#include "ImGuiWrapper.h"
#include "ImGuiOpenGlWrapper.h"

using namespace SYE;

namespace SYE 
{

class UiManager :
  public BaseModule
{
public:
  UiManager() = delete;

  UiManager(BaseModule &parentModule);
  ~UiManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


  // ImGUI.
  bool InitializeImGui(std::shared_ptr<Window> pWindow);
  void InitializeImGuiDraw();
  void DrawImGui();
  bool TerminateImGui();

private:
  
};

}
