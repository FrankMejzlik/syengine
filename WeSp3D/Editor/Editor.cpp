
#include "macros.h"
#include "Editor.h"
#include "EditorWindow.h"

using namespace WeSp;

Editor::Editor(Instance* pInstance, std::shared_ptr<EngineAPI> pEngineAPI):
  IUsesEngineAPI(pEngineAPI),
  _pInstance(pInstance),
  _pMainEditorWindow(nullptr)
{}

Editor::~Editor()
{
  // Clean after self
  wxEntryCleanup();

  SAFE_DELETE(_pMainEditorWindow);
}

bool Editor::OnInit() 
{ 
  if (!wxApp::OnInit())
  {
    return false;
  }

  // Instantiate main editor window and show it
  _pMainEditorWindow = new EditorWindow(
    this, 
    _pEngineAPI,
    _pInstance->GetScreenWidth(), 
    _pInstance->GetScreenHeight(),  
    "WeSp3D Engine Editor"
  );
  _pMainEditorWindow->Show(true);

  printf("Editor initialzied...\n");
  return true;
}

Instance* Editor::GetPInstance()
{
  return _pInstance;
}
