
#include "ListControl.h"
#include "EditorWindow.h"

using namespace WeSp;

const wxChar *SMALL_VIRTUAL_VIEW_ITEMS[][2] =
{
  { wxT("Cat"), wxT("meow") },
{ wxT("Cow"), wxT("moo") },
{ wxT("Crow"), wxT("caw") },
{ wxT("Dog"), wxT("woof") },
{ wxT("Duck"), wxT("quack") },
{ wxT("Mouse"), wxT("squeak") },
{ wxT("Owl"), wxT("hoo") },
{ wxT("Pig"), wxT("oink") },
{ wxT("Pigeon"), wxT("coo") },
{ wxT("Sheep"), wxT("baaah") },
};

// number of items in icon/small icon view
static const int NUM_ICONS = 9;

int wxCALLBACK
MyCompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
  // inverse the order
  if (item1 < item2)
    return 1;
  if (item1 > item2)
    return -1;

  return 0;
}


wxBEGIN_EVENT_TABLE(ListControl, wxListCtrl)
//EVT_LIST_BEGIN_DRAG(CTRL_LIST, ListControl::OnBeginDrag)
//EVT_LIST_BEGIN_RDRAG(CTRL_LIST, ListControl::OnBeginRDrag)
//EVT_LIST_BEGIN_LABEL_EDIT(CTRL_LIST, ListControl::OnBeginLabelEdit)
//EVT_LIST_END_LABEL_EDIT(CTRL_LIST, ListControl::OnEndLabelEdit)
//EVT_LIST_DELETE_ITEM(CTRL_LIST, ListControl::OnDeleteItem)
//EVT_LIST_DELETE_ALL_ITEMS(CTRL_LIST, ListControl::OnDeleteAllItems)
//EVT_LIST_ITEM_SELECTED(CTRL_LIST, ListControl::OnSelected)
//EVT_LIST_ITEM_DESELECTED(CTRL_LIST, ListControl::OnDeselected)
//EVT_LIST_KEY_DOWN(CTRL_LIST, ListControl::OnListKeyDown)
//EVT_LIST_ITEM_ACTIVATED(CTRL_LIST, ListControl::OnActivated)
//EVT_LIST_ITEM_FOCUSED(CTRL_LIST, ListControl::OnFocused)
EVT_LIST_ITEM_RIGHT_CLICK(CTRL_LIST, ListControl::OnListItemRightClick)
EVT_MENU(CONTEXT_RIGHT_CLICK_MENU_DELETE_OBJECT, ListControl::OnContextDeleteObject)


//EVT_LIST_COL_CLICK(CTRL_LIST, ListControl::OnColClick)
//EVT_LIST_COL_RIGHT_CLICK(CTRL_LIST, ListControl::OnColRightClick)
//EVT_LIST_COL_BEGIN_DRAG(CTRL_LIST, ListControl::OnColBeginDrag)
//EVT_LIST_COL_DRAGGING(CTRL_LIST, ListControl::OnColDragging)
//EVT_LIST_COL_END_DRAG(CTRL_LIST, ListControl::OnColEndDrag)

//EVT_LIST_CACHE_HINT(CTRL_LIST, ListControl::OnCacheHint)

#if USE_CONTEXT_MENU
EVT_CONTEXT_MENU(ListControl::OnContextMenu)
#endif
EVT_CHAR(ListControl::OnChar)

EVT_RIGHT_DOWN(ListControl::OnRightClick)
wxEND_EVENT_TABLE()

void ListControl::OnCacheHint(wxListEvent& event)
{
  wxLogMessage(wxT("OnCacheHint: cache items %ld..%ld"),
    event.GetCacheFrom(), event.GetCacheTo());
}

void ListControl::SetColumnImage(int col, int image)
{
  wxListItem item;
  item.SetMask(wxLIST_MASK_IMAGE);
  item.SetImage(image);
  SetColumn(col, item);
}

void ListControl::OnColClick(wxListEvent& event)
{
  int col = event.GetColumn();

  // set or unset image
  static bool x = false;
  x = !x;
  SetColumnImage(col, x ? 0 : -1);

  wxLogMessage(wxT("OnColumnClick at %d."), col);
}

void ListControl::OnListItemRightClick(wxListEvent & event)
{
  if (1)
  {
    wxListItem info;
    info.m_itemId = event.m_itemIndex;
    info.m_col = 0;
    info.m_mask = wxLIST_MASK_TEXT;
    if (GetItem(info))
    {

      long value;
      (info.m_text).ToLong(&value);
      lastRclicked = value;
    }
    else
    {
      wxFAIL_MSG(wxT("wxListCtrl::GetItem() failed"));
    }
  }

  // Show popupmenu at position
  wxMenu menu(wxT("Test"));
  menu.Append(CONTEXT_RIGHT_CLICK_MENU_DELETE_OBJECT, wxT("&Delete object from scene"));

  PopupMenu(&menu, event.GetPoint());

}

void ListControl::OnContextDeleteObject(wxCommandEvent& event)
{
  std::vector<int> cmdData;
  cmdData.push_back(lastRclicked);
  _pEngineAPI->PushEngineCommand(eCommandType::DeleteObjectId, cmdData);
}

void ListControl::OnColRightClick(wxListEvent& event)
{
  int col = event.GetColumn();
  if (col != -1)
  {
    SetColumnImage(col, -1);
  }

  // Show popupmenu at position
  wxMenu menu(wxT("Test"));
  PopupMenu(&menu, event.GetPoint());

  wxLogMessage(wxT("OnColumnRightClick at %d."), event.GetColumn());
}

void ListControl::LogColEvent(const wxListEvent& event, const wxChar *name)
{
  const int col = event.GetColumn();

  wxLogMessage(wxT("%s: column %d (width = %d or %d)."),
    name,
    col,
    event.GetItem().GetWidth(),
    GetColumnWidth(col));
}

void ListControl::OnColBeginDrag(wxListEvent& event)
{
  LogColEvent(event, wxT("OnColBeginDrag"));

  if (event.GetColumn() == 0)
  {
    wxLogMessage(wxT("Resizing this column shouldn't work."));

    event.Veto();
  }
}

void ListControl::OnColDragging(wxListEvent& event)
{
  LogColEvent(event, wxT("OnColDragging"));
}

void ListControl::OnColEndDrag(wxListEvent& event)
{
  LogColEvent(event, wxT("OnColEndDrag"));
}

void ListControl::OnBeginDrag(wxListEvent& event)
{
  const wxPoint& pt = event.m_pointDrag;

  int flags;
  wxLogMessage(wxT("OnBeginDrag at (%d, %d), item %ld."),
    pt.x, pt.y, HitTest(pt, flags));
}

void ListControl::OnBeginRDrag(wxListEvent& event)
{
  wxLogMessage(wxT("OnBeginRDrag at %d,%d."),
    event.m_pointDrag.x, event.m_pointDrag.y);
}

void ListControl::OnBeginLabelEdit(wxListEvent& event)
{
  wxLogMessage(wxT("OnBeginLabelEdit: %s"), event.m_item.m_text.c_str());

  wxTextCtrl * const text = GetEditControl();
  if (!text)
  {
    wxLogMessage("BUG: started to edit but no edit control");
  }
  else
  {
    wxLogMessage("Edit control value: \"%s\"", text->GetValue());
  }
}

void ListControl::OnEndLabelEdit(wxListEvent& event)
{
  wxLogMessage(wxT("OnEndLabelEdit: %s"),
    (
      event.IsEditCancelled() ?
      wxString("[cancelled]") :
      event.m_item.m_text
      ).c_str()
  );
}

void ListControl::OnDeleteItem(wxListEvent& event)
{
  LogEvent(event, wxT("OnDeleteItem"));
  wxLogMessage(wxT("Number of items when delete event is sent: %d"), GetItemCount());
}

void ListControl::OnDeleteAllItems(wxListEvent& event)
{
  LogEvent(event, wxT("OnDeleteAllItems"));
}

void ListControl::OnSelected(wxListEvent& event)
{
  LogEvent(event, wxT("OnSelected"));

  if (GetWindowStyle() & wxLC_REPORT)
  {
    wxListItem info;
    info.m_itemId = event.m_itemIndex;
    info.m_col = 1;
    info.m_mask = wxLIST_MASK_TEXT;
    if (GetItem(info))
    {
      wxLogMessage(wxT("Value of the 2nd field of the selected item: %s"),
        info.m_text.c_str());
    }
    else
    {
      wxFAIL_MSG(wxT("wxListCtrl::GetItem() failed"));
    }
  }
}

void ListControl::OnDeselected(wxListEvent& event)
{
  LogEvent(event, wxT("OnDeselected"));
}

void ListControl::OnActivated(wxListEvent& event)
{
  LogEvent(event, wxT("OnActivated"));
}

void ListControl::OnFocused(wxListEvent& event)
{
  LogEvent(event, wxT("OnFocused"));

  event.Skip();
}

void ListControl::OnListKeyDown(wxListEvent& event)
{
  long item;

  if (!wxGetKeyState(WXK_SHIFT))
  {
    LogEvent(event, wxT("OnListKeyDown"));
    event.Skip();
    return;
  }

  switch (event.GetKeyCode())
  {
  case 'C': // colorize
  {
    wxListItem info;
    info.m_itemId = event.GetIndex();
    if (info.m_itemId == -1)
    {
      // no item
      break;
    }

    GetItem(info);

    wxListItemAttr *attr = info.GetAttributes();
    if (!attr || !attr->HasTextColour())
    {
      info.SetTextColour(*wxCYAN);

      SetItem(info);

      RefreshItem(info.m_itemId);
    }
  }
  break;

  case 'N': // next
    item = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_FOCUSED);
    if (item++ == GetItemCount() - 1)
    {
      item = 0;
    }

    wxLogMessage(wxT("Focusing item %ld"), item);

    SetItemState(item, wxLIST_STATE_FOCUSED, wxLIST_STATE_FOCUSED);
    EnsureVisible(item);
    break;

  case 'R': // show bounding rectangle
  {
    item = event.GetIndex();
    wxRect r;
    if (!GetItemRect(item, r))
    {
      wxLogError(wxT("Failed to retrieve rect of item %ld"), item);
      break;
    }

    wxLogMessage(wxT("Bounding rect of item %ld is (%d, %d)-(%d, %d)"),
      item, r.x, r.y, r.x + r.width, r.y + r.height);
  }
  break;

  case '1': // show sub item bounding rectangle for the given column
  case '2': // (and icon/label rectangle if Shift/Ctrl is pressed)
  case '3':
  case '4': // this column is invalid but we want to test it too
    if (InReportView())
    {
      int subItem = event.GetKeyCode() - '1';
      item = event.GetIndex();
      wxRect r;

      int code = wxLIST_RECT_BOUNDS;
      if (wxGetKeyState(WXK_SHIFT))
        code = wxLIST_RECT_ICON;
      else if (wxGetKeyState(WXK_CONTROL))
        code = wxLIST_RECT_LABEL;

      if (!GetSubItemRect(item, subItem, r, code))
      {
        wxLogError(wxT("Failed to retrieve rect of item %ld column %d"), item, subItem + 1);
        break;
      }

      wxLogMessage(wxT("Bounding rect of item %ld column %d is (%d, %d)-(%d, %d)"),
        item, subItem + 1,
        r.x, r.y, r.x + r.width, r.y + r.height);
    }
    break;

  case 'U': // update
    if (!IsVirtual())
      break;

    if (m_updated != -1)
      RefreshItem(m_updated);

    m_updated = event.GetIndex();
    if (m_updated != -1)
    {
      // we won't see changes to this item as it's selected, update
      // the next one (or the first one if we're on the last item)
      if (++m_updated == GetItemCount())
        m_updated = 0;

      wxLogMessage("Updating colour of the item %ld", m_updated);
      RefreshItem(m_updated);
    }
    break;

  case 'D': // delete
    item = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while (item != -1)
    {
      DeleteItem(item);

      wxLogMessage(wxT("Item %ld deleted"), item);

      // -1 because the indices were shifted by DeleteItem()
      item = GetNextItem(item - 1,
        wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    break;

  case 'I': // insert
    if (GetWindowStyle() & wxLC_REPORT)
    {
      if (GetWindowStyle() & wxLC_VIRTUAL)
      {
        SetItemCount(GetItemCount() + 1);
      }
      else // !virtual
      {
        InsertItemInReportView(event.GetIndex());
      }
    }
    //else: fall through

  default:
    LogEvent(event, wxT("OnListKeyDown"));

    event.Skip();
  }
}

void ListControl::OnChar(wxKeyEvent& event)
{
  wxLogMessage(wxT("Got char event."));

  event.Skip();
}

void ListControl::OnRightClick(wxMouseEvent& event)
{
  if (!event.ControlDown())
  {
    event.Skip();
    return;
  }

  int flags;
  long subitem;
  long item = HitTest(event.GetPosition(), flags, &subitem);

  wxString where;
  switch (flags)
  {
  case wxLIST_HITTEST_ABOVE: where = wxT("above"); break;
  case wxLIST_HITTEST_BELOW: where = wxT("below"); break;
  case wxLIST_HITTEST_NOWHERE: where = wxT("nowhere near"); break;
  case wxLIST_HITTEST_ONITEMICON: where = wxT("on icon of"); break;
  case wxLIST_HITTEST_ONITEMLABEL: where = wxT("on label of"); break;
  case wxLIST_HITTEST_ONITEMRIGHT: where = wxT("right on"); break;
  case wxLIST_HITTEST_TOLEFT: where = wxT("to the left of"); break;
  case wxLIST_HITTEST_TORIGHT: where = wxT("to the right of"); break;
  default: where = wxT("not clear exactly where on"); break;
  }

  wxLogMessage(wxT("Right double click %s item %ld, subitem %ld"),
    where.c_str(), item, subitem);
}

void ListControl::LogEvent(const wxListEvent& event, const wxChar *eventName)
{
  /*wxLogMessage(wxT("Item %ld: %s (item text = %s, data = %ld)"),
    event.GetIndex(), eventName,
    event.GetText(), static_cast<long>(event.GetData()));*/
}

wxString ListControl::OnGetItemText(long item, long column) const
{
  if (GetItemCount() == WXSIZEOF(SMALL_VIRTUAL_VIEW_ITEMS))
  {
    return SMALL_VIRTUAL_VIEW_ITEMS[item][column];
  }
  else // "big" virtual control
  {
    return wxString::Format(wxT("Column %ld of item %ld"), column, item);
  }
}

int ListControl::OnGetItemColumnImage(long item, long column) const
{
  if (!column)
    return 0;

  if (!(item % 3) && column == 1)
    return 0;

  return -1;
}

wxListItemAttr *ListControl::OnGetItemAttr(long item) const
{
  // test to check that RefreshItem() works correctly: when m_updated is
  // set to some item and it is refreshed, we highlight the item
  if (item == m_updated)
  {
    static wxListItemAttr s_attrHighlight(*wxRED, wxNullColour, wxNullFont);
    return &s_attrHighlight;
  }

  return wxListCtrl::OnGetItemAttr(item);
}

void ListControl::InsertItemInReportView(int i)
{
  wxString buf;
  buf.Printf(wxT("This is item %d"), i);
  long tmp = InsertItem(i, buf, 0);
  SetItemData(tmp, i);

  buf.Printf(wxT("Col 1, item %d"), i);
  SetItem(tmp, 1, buf);

  buf.Printf(wxT("Item %d in column 2"), i);
  SetItem(tmp, 2, buf);
}

#if USE_CONTEXT_MENU
void ListControl::OnContextMenu(wxContextMenuEvent& event)
{
  if (GetEditControl() == NULL)
  {
    wxPoint point = event.GetPosition();
    // If from keyboard
    if ((point.x == -1) && (point.y == -1))
    {
      wxSize size = GetSize();
      point.x = size.x / 2;
      point.y = size.y / 2;
    }
    else
    {
      point = ScreenToClient(point);
    }
    ShowContextMenu(point);
  }
  else
  {
    // the user is editing:
    // allow the text control to display its context menu
    // if it has one (it has on Windows) rather than display our one
    event.Skip();
  }
}
#endif

void ListControl::ShowContextMenu(const wxPoint& pos)
{
  wxMenu menu;

  menu.Append(wxID_ABOUT, wxT("&About"));
  menu.AppendSeparator();
  menu.Append(wxID_EXIT, wxT("E&xit"));

  PopupMenu(&menu, pos.x, pos.y);
}