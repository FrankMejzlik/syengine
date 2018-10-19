#pragma once

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

#include "wx/imaglist.h"
#include "wx/listctrl.h"
#include "wx/timer.h"        
#include "wx/colordlg.h"     
#include "wx/settings.h"
#include "wx/sysopt.h"
#include "wx/numdlg.h"

#include <queue>

#include "config_editor.h"
#include "wxWidgetsEnums.h"

#include "Command.h"
#include "IUsesEngineAPI.h"

using namespace WeSp;

namespace WeSp 
{

class EditorWindow;

class ListControl : 
  public wxListCtrl, public IUsesEngineAPI
{
public:
  ListControl(
    EditorWindow* pParentInstance,
    std::shared_ptr<EngineAPI> pEngineAPI,
    wxWindow* parent,
    const wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style
  ): 
    IUsesEngineAPI(pEngineAPI),
    _pParentInstance(pParentInstance),
    wxListCtrl(parent, id, pos, size, style)
  {
    m_updated = -1;
  }

  // add one item to the listctrl in report mode
  void InsertItemInReportView(int i);

  int lastRclicked = -1;

  void OnColClick(wxListEvent& event);
  void OnListItemRightClick(wxListEvent& event);
  void OnContextDeleteObject(wxCommandEvent& event);
  void OnColRightClick(wxListEvent& event);
  void OnColBeginDrag(wxListEvent& event);
  void OnColDragging(wxListEvent& event);
  void OnColEndDrag(wxListEvent& event);
  void OnBeginDrag(wxListEvent& event);
  void OnBeginRDrag(wxListEvent& event);
  void OnBeginLabelEdit(wxListEvent& event);
  void OnEndLabelEdit(wxListEvent& event);
  void OnDeleteItem(wxListEvent& event);
  void OnDeleteAllItems(wxListEvent& event);
  void OnSelected(wxListEvent& event);
  void OnDeselected(wxListEvent& event);
  void OnListKeyDown(wxListEvent& event);
  void OnActivated(wxListEvent& event);
  void OnFocused(wxListEvent& event);
  void OnCacheHint(wxListEvent& event);

  void OnChar(wxKeyEvent& event);

#if USE_CONTEXT_MENU
  void OnContextMenu(wxContextMenuEvent& event);
#endif

  void OnRightClick(wxMouseEvent& event);

private:





  EditorWindow* _pParentInstance;



  void ShowContextMenu(const wxPoint& pos);
  wxLog *m_logOld;
  void SetColumnImage(int col, int image);

  void LogEvent(const wxListEvent& event, const wxChar *eventName);
  void LogColEvent(const wxListEvent& event, const wxChar *eventName);

  virtual wxString OnGetItemText(long item, long column) const;
  virtual int OnGetItemColumnImage(long item, long column) const;
  virtual wxListItemAttr *OnGetItemAttr(long item) const;

  long m_updated;


  wxDECLARE_NO_COPY_CLASS(ListControl);
  wxDECLARE_EVENT_TABLE();
};

}