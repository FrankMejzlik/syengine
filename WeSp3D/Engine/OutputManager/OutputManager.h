#pragma once

#include <vector>

#include "BaseModule.h"

// Submodules.
#include "RenderingManager.h"
#include "AudioManager.h"
//#include "OtherInputManager.h"

using namespace WeSp;

enum class eWindowType
{
  MAIN_GAME_WINDOW,
  COUNT
};

namespace WeSp {

class OutputManager :
  public BaseModule
{
public:
  OutputManager() = delete;

  OutputManager(BaseModule &parentModule);
  ~OutputManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height);


private:
 
};

}