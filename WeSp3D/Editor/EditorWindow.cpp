
#include "EditorWindow.h"

using namespace WeSp;

/**
* Event table for main editor window
*/
wxBEGIN_EVENT_TABLE(EditorWindow, wxFrame)

EVT_MENU(MENU_ADD, EditorWindow::OnMenuAdd)
EVT_MENU(MENU_QUIT, EditorWindow::OnQuit)
EVT_PAINT(EditorWindow::OnPaint)
EVT_IDLE(EditorWindow::OnIdle)
EVT_MENU(MENU_ABOUT, EditorWindow::OnAbout)
EVT_COMBOBOX(PANEL_ADD_TO_SCENE_CTRL_ADD_COMBO_BOX, EditorWindow::OnAddToSceneComboBoxSelect)
EVT_BUTTON(PANEL_ADD_TO_SCENE_CREATE_BUTTON, EditorWindow::OnAddToSceneCreateButtonClicked)

wxEND_EVENT_TABLE()

EditorWindow::EditorWindow(
  Editor* pParentInstance, 
  std::shared_ptr<EngineApi> pEngineAPI,
  size_t windowWidth, size_t windowHeight, 
  const wxString& title
) :
  IUsesEngineAPI(pEngineAPI),
  _pParentInstance(pParentInstance),
  wxFrame(
    NULL, wxID_ANY, title,
    wxPoint(EDITOR_DEFAULT_POS_X, EDITOR_DEFAULT_POS_Y),
    wxSize(EDITOR_DEFAULT_WIDTH, windowHeight - 30)
  )
{

  _panelAddToScene = NULL;
  _panelAddToScene_selectComboBox = NULL;
  _panelAddToScene_buttonCreate = NULL;
  _panelLog_logWindow = NULL;
  _panelLog = NULL;
  _panelSceneObjects = NULL;
  _panelSceneObjects_objectList = NULL;

  m_numListItems = 10;

  // set the frame icon
  SetIcon(wxICON(sample));

#if SHOW_MAIN_MENU
  // create a menu bar
  wxMenu *fileMenu = new wxMenu;
  fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

  // the "About" item should be in the help menu
  wxMenu* addMenu = new wxMenu;
  addMenu->Append(MENU_ADD, "A&dd\tF1", "Adds things into scene");

  // the "About" item should be in the help menu
  wxMenu *helpMenu = new wxMenu;
  helpMenu->Append(MENU_ABOUT, "&About\tF1", "Show about dialog");

  // now append the freshly created menu to the menu bar...
  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, "&File");
  menuBar->Append(addMenu, "&Add");
  menuBar->Append(helpMenu, "&Help");

  SetMenuBar(menuBar);
#endif // SHOW_MAIN_STATUS_BAR

#if SHOW_MAIN_STATUS_BAR
  // create a status bar just for fun (by default with 1 pane only)
  CreateStatusBar(2);
  SetStatusText(WELCOME_STATUS_BAR);
#endif // SHOW_MAIN_STATUS_BAR

  _panelAddToScene = new wxPanel(this, PANEL_ADD_TO_SCENE, wxPoint(10, 10), wxSize(100, 100), wxTRANSPARENT_WINDOW);
  _panelSceneObjects = new wxPanel(this, PANEL_SCENE_OBJECT_LIST, wxPoint(10, 100), wxSize(100, 100), wxTRANSPARENT_WINDOW);
  _panelLog = new wxPanel(this, PANEL_LOG, wxPoint(10, 300), wxSize(100, 100), wxTRANSPARENT_WINDOW);
  //_panelAddToScene->SetBackgroundColour(wxColour(*wxBLACK));
  _panelSceneObjects->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
  _panelLog->SetBackgroundColour(wxColour(*wxWHITE));

  _panelLog_logWindow = new wxTextCtrl(
    _panelLog, wxID_ANY, wxEmptyString,
    wxDefaultPosition, wxDefaultSize,
    wxTE_READONLY | wxTE_MULTILINE | wxSUNKEN_BORDER
  );

  // Create list
  RecreateList(wxLC_LIST, false);
  CreateAddToScenePanel();


  // Scale things
  DoSize();
}

EditorWindow::~EditorWindow()
{
  delete _panelAddToScene;
  delete _panelLog;
  delete _panelSceneObjects;
}

void EditorWindow::OnQuit(wxCommandEvent& event)
{
  // true is to force the frame to close
  Close(false);
}

void EditorWindow::OnMenuAdd(wxCommandEvent& event)
{
  RecreateList(wxLC_LIST, false);
}

void EditorWindow::OnAbout(wxCommandEvent& event)
{
  wxMessageBox(wxString::Format
  (
    "Welcome to %s!\n"
    "\n"
    "This is the minimal wxWidgets sample\n"
    "running under %s.",
    wxVERSION_STRING,
    wxGetOsDescription()
  ),
    "About wxWidgets minimal sample",
    wxOK | wxICON_INFORMATION,
    this);
}

void EditorWindow::RecreateList(long flags, bool withText)
{

  delete _panelSceneObjects_objectList;

  _panelSceneObjects_objectList = new ListControl(
    this,
    _pEngineAPI,
    _panelSceneObjects,
    CTRL_LIST,
    wxDefaultPosition, wxDefaultSize,
    flags |
    wxBORDER_THEME | wxLC_EDIT_LABELS);

  //_panelSceneObjects_objectList->AppendColumn("ID", wxLIST_FORMAT_RIGHT, 100);


  InitWithListItems();
}

void EditorWindow::InitWithListItems()

{
  for (int i = 0; i < m_numListItems; i++)
  {
    //_panelSceneObjects_objectList->InsertItem(i, wxString::Format(wxT("Item %d"), i));
  }
}

Editor * WeSp::EditorWindow::GetPParent() const
{
  return _pParentInstance;
}

void EditorWindow::CreateAddToScenePanel()
{

  // Add to scene combo box
  _panelAddToScene_selectComboBox = new wxComboBox(
    _panelAddToScene, PANEL_ADD_TO_SCENE_CTRL_ADD_COMBO_BOX, "please select",
    wxDefaultPosition, wxSize(200, -1));

  // Push options
  _panelAddToScene_selectComboBox->Append(OBJECT_TYPE1);
  _panelAddToScene_selectComboBox->Append(OBJECT_TYPE2);
  _panelAddToScene_selectComboBox->Append(OBJECT_TYPE3);
  _panelAddToScene_selectComboBox->Append(OBJECT_TYPE4);

  // Create button
  _panelAddToScene_buttonCreate = new wxButton(
    _panelAddToScene, PANEL_ADD_TO_SCENE_CREATE_BUTTON,
    _("Create"), 
    wxDefaultPosition, wxDefaultSize
  );

  // Initialize attribute subpanesl
  // OBJECT_TYPE1: Block
  _panelsAddToScene.push_back(new wxPanel(_panelAddToScene, PANEL_ADD_TO_SCENE_PANEL_ATTR_1));
  {
    _label11 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "x pos",
      wxPoint(0, 0), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT |wxNO_BORDER);

    _input11 = new wxTextCtrl(_panelsAddToScene[0], INPUT1, "",
      wxPoint(160, 0), wxSize(100, 20),
      NULL);

    _label12 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "y pos",
      wxPoint(0, 25), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input12 = new wxTextCtrl(_panelsAddToScene[0], INPUT2, "",
      wxPoint(160, 25), wxSize(100, 20),
      NULL);

    _label13 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "z pos",
      wxPoint(0, 50), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input13 = new wxTextCtrl(_panelsAddToScene[0], INPUT3, "",
      wxPoint(160, 50), wxSize(100, 20),
      NULL);

    _label14 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "width",
      wxPoint(0, 75), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input14 = new wxTextCtrl(_panelsAddToScene[0], INPUT4, "",
      wxPoint(160, 75), wxSize(100, 20),
      NULL);

    _label15 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "height",
      wxPoint(0, 100), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input15 = new wxTextCtrl(_panelsAddToScene[0], INPUT5, "",
      wxPoint(160, 100), wxSize(100, 20),
      NULL);

    _label16 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "length",
      wxPoint(0, 125), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input16 = new wxTextCtrl(_panelsAddToScene[0], INPUT6, "",
      wxPoint(160, 125), wxSize(100, 20),
      NULL);




    _label17 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "rotation axis x",
      wxPoint(0, 150), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input17 = new wxTextCtrl(_panelsAddToScene[0], INPUT7, "",
      wxPoint(160, 150), wxSize(100, 20),
      NULL);

    _label18 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "rotation axis y",
      wxPoint(0, 175), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input18 = new wxTextCtrl(_panelsAddToScene[0], INPUT8, "",
      wxPoint(160, 175), wxSize(100, 20),
      NULL);

    _label19 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "rotation axis z",
      wxPoint(0, 200), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input19 = new wxTextCtrl(_panelsAddToScene[0], INPUT9, "",
      wxPoint(160, 200), wxSize(100, 20),
      NULL);

    _label110 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "angle (in degrees)",
      wxPoint(0, 225), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input110 = new wxTextCtrl(_panelsAddToScene[0], INPUT10, "",
      wxPoint(160, 225), wxSize(100, 20),
      NULL);


    _label111 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "scale in x axis",
      wxPoint(0, 250), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input111 = new wxTextCtrl(_panelsAddToScene[0], INPUT11, "",
      wxPoint(160, 250), wxSize(100, 20),
      NULL);

    _label112 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "scale in y axis",
      wxPoint(0, 275), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input112 = new wxTextCtrl(_panelsAddToScene[0], INPUT12, "",
      wxPoint(160, 275), wxSize(100, 20),
      NULL);

    _label113 = new wxTextCtrl(_panelsAddToScene[0], wxID_ANY, "scale in z axis",
      wxPoint(0, 300), wxSize(150, 20),
      wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER);

    _input113 = new wxTextCtrl(_panelsAddToScene[0], INPUT13, "",
      wxPoint(160, 300), wxSize(100, 20),
      NULL);

    _panelsAddToScene[0]->Hide();

    // OBJECT_TYPE2: Spere/ellipsoid
    _panelsAddToScene.push_back(new wxPanel(_panelAddToScene, PANEL_ADD_TO_SCENE_PANEL_ATTR_2));

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label1",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "X position",
          wxPoint(0, 0), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input1",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT1, "",
          wxPoint(160, 0), wxSize(100, 20),
          NULL
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label2",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "Y position",
          wxPoint(0, 25), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input2",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT2, "",
          wxPoint(160, 25), wxSize(100, 20),
          NULL
        )
        )
    );
    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label3",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "Z position",
          wxPoint(0, 50), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input3",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT3, "",
          wxPoint(160, 50), wxSize(100, 20),
          NULL
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label4",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "x radius",
          wxPoint(0, 75), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input4",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT4, "",
          wxPoint(160, 75), wxSize(100, 20),
          NULL
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label5",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "y radius",
          wxPoint(0, 100), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input5",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT5, "",
          wxPoint(160, 100), wxSize(100, 20),
          NULL
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label6",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "z radius",
          wxPoint(0, 125), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input6",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT6, "",
          wxPoint(160, 125), wxSize(100, 20),
          NULL
        )
        )
    );
    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label7",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "x scale",
          wxPoint(0, 150), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input7",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT7, "",
          wxPoint(160, 150), wxSize(100, 20),
          NULL
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label8",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "y scale",
          wxPoint(0, 175), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input8",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT8, "",
          wxPoint(160, 175), wxSize(100, 20),
          NULL
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"label9",
        new wxTextCtrl(
          _panelsAddToScene[1], wxID_ANY, "z scale",
          wxPoint(0, 200), wxSize(150, 20),
          wxTE_READONLY | wxTE_RIGHT | wxNO_BORDER
        )
        )
    );

    _controlsAddToScene_objectType2.insert(
      std::pair<std::wstring, wxTextCtrl*>(
        L"input9",
        new wxTextCtrl(
          _panelsAddToScene[1], PANEL_ADD_TO_SCENE_PANEL_ATTR_2_INPUT9, "",
          wxPoint(160, 200), wxSize(100, 20),
          NULL
        )
        )
    );
  }


  _panelsAddToScene[1]->Hide();

}

void EditorWindow::OnSize(wxSizeEvent & event)
{
  DoSize();

  event.Skip();
}


void EditorWindow::OnAddToSceneComboBoxSelect(wxCommandEvent & event)
{
  switch (GetObjectTypeFromString(_panelAddToScene_selectComboBox->GetValue()))
  {
  case 1:
    printf("selected 1\n");
    ShowAddToSceneAttrPanel(0);
    break;

  case 2:
    printf("selected 2\n");
    ShowAddToSceneAttrPanel(1);
    break;

  case 3:
    printf("selected 3\n");
    ShowAddToSceneAttrPanel(2);
    break;

  case 4:
    printf("selected 4\n");
    ShowAddToSceneAttrPanel(3);
    break;

  }
}

int EditorWindow::GetObjectTypeFromString(wxString type)
{
  if (type == OBJECT_TYPE1)
  {
    return 1;
  }

  if (type == OBJECT_TYPE2)
  {
    return 2;
  }

  if (type == OBJECT_TYPE3)
  {
    return 3;
  }

  if (type == OBJECT_TYPE4)
  {
    return 4;
  }
  return 0;
}

void EditorWindow::ShowAddToSceneAttrPanel(int type)
{
  int i = 0;
  for (std::vector<wxPanel*>::iterator it = _panelsAddToScene.begin(); it != _panelsAddToScene.end(); ++it)
  {
    if (i == type)
    {
      (*it)->Show();
    }
    else
    {
      (*it)->Hide();
    }
    ++i;
  }
}

void EditorWindow::OnAddToSceneCreateButtonClicked(wxCommandEvent& event)
{
  // If Block
  if (GetObjectTypeFromString(_panelAddToScene_selectComboBox->GetValue()) == 1)
  {
    std::vector<float> floatData;

    double value = 0.0f;
    wxString stdData = _input11->GetValue();
       
    stdData.ToDouble(&value);
    floatData.push_back((float)value);

    stdData = L"";
    stdData = _input12->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input13->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);



    stdData = L"";
    stdData = _input14->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input15->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input16->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);



    stdData = L"";
    stdData = _input17->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input18->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input19->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input110->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);



    stdData = L"";
    stdData = _input111->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input112->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input112->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);

    _pEngineAPI->PushEngineCommand(eCommandType::CreateBlock, floatData);
  }
  // If Sphere/ellipsoid
  else if (GetObjectTypeFromString(_panelAddToScene_selectComboBox->GetValue()) == 2)
  {
    std::vector<float> floatData;

    double value = 0.0f;

    wxString stdData = _controlsAddToScene_objectType2.find(L"input1")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);

    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input2")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input3")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);



    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input4")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input5")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input6")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);



    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input7")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input8")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input9")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);

    /*stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input10")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);



    stdData = L"";
    stdData = _controlsAddToScene_objectType2.find(L"input11")->second->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input112->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);
    stdData = L"";
    stdData = _input112->GetValue();
    stdData.ToDouble(&value);
    floatData.push_back((float)value);*/

    for (std::vector<float>::iterator it = floatData.begin(); it != floatData.end(); ++it)
    {
    }
    _pEngineAPI->PushEngineCommand(eCommandType::CreateSphere, floatData);
  }
  else
  {
    printf("not implemented yet\n");
  }
}

void EditorWindow::DoSize()
{

  // TODO: existence check
  wxSize size = GetClientSize();

  // Scale "Add to scene" panel
  _panelAddToScene->SetSize(0, 0, (size.x / 2), size.y / 2);
  {
    _panelAddToScene_selectComboBox->SetSize(0, 0, 200, 20);
    _panelAddToScene_buttonCreate->SetSize(20, 35, 100, 20);

    // Sub-panels for atributes
    {
      for (std::vector<wxPanel*>::iterator it = _panelsAddToScene.begin(); it != _panelsAddToScene.end(); ++it)
      {
        (*it)->SetSize(
          0, _panelAddToScene->GetSize().y / 4,
          _panelAddToScene->GetSize().x, _panelAddToScene->GetSize().y * 0.75
        );
      }
    }
  }



  // Scale "Sceme objects" panel
  _panelSceneObjects->SetSize(size.x / 2, 0, (size.x / 2), size.y / 2);
  _panelSceneObjects_objectList->SetSize(
    0, 0,
    _panelSceneObjects->GetSize().x, _panelSceneObjects->GetSize().y
  );

  // Scale "Log" panel
  _panelLog->SetSize(
    0, size.y / 2,
    (size.x), size.y / 2
  );

  _panelLog_logWindow->SetSize(
    0, 0, 
    _panelLog->GetSize().x, _panelLog->GetSize().y
  );
}

void EditorWindow::ProcessCommands()
{
  while (!_pEngineAPI->GetEditorCommandQueue()->empty())
  {
    Command cmd(_pEngineAPI->GetEditorCommandQueue()->front());
    _pEngineAPI->GetEditorCommandQueue()->pop();

    switch (cmd.GetType())
    {
    case eCommandType::CreatedObjectId:
      HandleCommand_CreatedObjectId(cmd.GetIntData());
      break;

    case eCommandType::DeletedObjectId:
      HandleCommand_DeletedObjectId(cmd.GetIntData());
      break;

    case eCommandType::Terminate:
      HandleCommand_Terminate();
      break;
    }
  }
}