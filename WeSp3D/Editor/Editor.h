#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif-----------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

#include <queue>

#include "Command.h"
#include "IUsesEngineAPI.h"
#include "Instance.h"

using namespace WeSp;

namespace WeSp 
{
// Forward declarations
class EditorWindow;

class Editor :
  public wxApp, public IUsesEngineAPI
{
public:
  Editor() = delete;
  Editor(Instance* pInstance, std::shared_ptr<EngineAPI> pEngineAPI);
  ~Editor();

  virtual bool OnInit();

  Instance* GetPInstance();

private:
  Instance* _pInstance;
  EditorWindow* _pMainEditorWindow;

  std::queue<Command>* _pEngineCommandQueue;
  std::queue<Command>* _pEditorCommandQueue;

};

}
