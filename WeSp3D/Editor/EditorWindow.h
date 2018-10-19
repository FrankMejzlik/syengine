#pragma once


#include <vector>
#include <queue>
#include <map>
#include "Command.h"

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

#include "config_editor.h"
#include "ListControl.h"

#include "wxWidgetsEnums.h"
#include "IUsesEngineAPI.h"
#include "EngineAPI.h"
#include "Editor.h"


using namespace WeSp;

namespace WeSp 
{

class EditorWindow :
  public wxFrame, public IUsesEngineAPI
{
public:  
  int m_numListItems;

  EditorWindow(
    Editor* pParentInstance, 
    std::shared_ptr<EngineAPI> pEngineAPI,
    size_t windowWidth, size_t windowHeight, 
    const wxString& title 
  );
  ~EditorWindow();

  // event handlers (these functions should _not_ be virtual)
  void OnQuit(wxCommandEvent& event);
  void OnMenuAdd(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

  void RecreateList(long flags, bool withText);

  void InitWithListItems();

private:
  // Pointer to parent instance, that owns this instance
  Editor* _pParentInstance;
  wxFrame _mainFrame;


  Editor* GetPParent() const;

  wxPanel* _panelAddToScene;
  wxComboBox* _panelAddToScene_selectComboBox;
  wxButton* _panelAddToScene_buttonCreate;
  
  wxPanel* _panelLog;
  wxTextCtrl* _panelLog_logWindow;

  wxPanel* _panelSceneObjects;
  ListControl* _panelSceneObjects_objectList;

  wxTextCtrl* _input11;
  wxTextCtrl* _label11;
  wxTextCtrl* _input12;
  wxTextCtrl* _label12;
  wxTextCtrl* _input13;
  wxTextCtrl* _label13;
  wxTextCtrl* _input14;
  wxTextCtrl* _label14;
  wxTextCtrl* _input15;
  wxTextCtrl* _label15;
  wxTextCtrl* _input16;
  wxTextCtrl* _label16;

  wxTextCtrl* _input17;
  wxTextCtrl* _label17;
  wxTextCtrl* _input18;
  wxTextCtrl* _label18;
  wxTextCtrl* _input19;
  wxTextCtrl* _label19;
  wxTextCtrl* _input110;
  wxTextCtrl* _label110;

  wxTextCtrl* _input111;
  wxTextCtrl* _label111;
  wxTextCtrl* _input112;
  wxTextCtrl* _label112;
  wxTextCtrl* _input113;
  wxTextCtrl* _label113;


  wxTextCtrl* _input21;
  wxTextCtrl* _input31;
  wxTextCtrl* _input41;


  std::map<std::wstring, wxTextCtrl*> _controlsAddToScene_objectType2;

  // List of all possible attributes for "Add to scene" functionality
  std::vector<wxPanel*> _panelsAddToScene;

  void CreateAddToScenePanel();
  void OnSize(wxSizeEvent& event);
  void OnAddToSceneComboBoxSelect(wxCommandEvent& event);
  int GetObjectTypeFromString(wxString type);
  void ShowAddToSceneAttrPanel(int type);
  void OnAddToSceneCreateButtonClicked(wxCommandEvent& event);


  void OnIdle(wxIdleEvent& event)
  {
    ProcessCommands();
  }

  void OnPaint(wxPaintEvent& event)
  {
    ProcessCommands();
  }

  void ProcessCommands();

  bool HandleCommand_DeletedObjectId(std::vector<int> intData)
  {
    int id = intData[0];

    wxString mystring = wxString::Format(wxT("%i"), id);

    long itemToDel = _panelSceneObjects_objectList->FindItem(0, mystring);
    _panelSceneObjects_objectList->DeleteItem(itemToDel);
    return true;
  }

  bool HandleCommand_CreatedObjectId(std::vector<int> createdId)
  {
    int id = createdId[0];
    _panelSceneObjects_objectList->InsertItem(id, wxString::Format(wxT("%d"), id));
    return true;
  }

  bool HandleCommand_Terminate()
  {
    if (!Close(false))
    {
      return false;
    }
    return true;
  }


  void DoSize();
    // any class wishing to process wxWidgets events must use this macro
  wxDECLARE_EVENT_TABLE();
};
}  