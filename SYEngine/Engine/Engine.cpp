
#include "Engine.h"

#include "Scene.h"
#include "Camera.h"
#include "ScriptHandler.h"

#include "PhysicsManager.h"

using namespace SYE;

Engine::Engine(ProcessInstance* pInstance) noexcept :
  BaseModule(MAGIC_BASE_MODULE_NUMBER), // Identify as root module.
  _pInstance(pInstance), // Save OS instance handle,
  _pOwningEngineContext(std::make_unique<EngineContext>())
{
  // Setup your own poniner
  SetEngineContextPtr(_pOwningEngineContext.get());

#if RUN_ENGINE_API

  // Insert EngineAPI instance.
  _subModules.insert(std::make_pair(ID_ENGINE_API, std::make_unique<EngineApi>(*this, _pOwningEngineContext.get())));
  // Set engine pointer to this.
  SetEngineApiPointer(static_cast<EngineApi*>(_subModules.find(ID_ENGINE_API)->second.get()));

#endif

  // Instantiate submodules.
  _subModules.insert(std::make_pair(ID_SCENE_MANAGER, std::make_unique<SceneManager>(*this, _pOwningEngineContext.get())));
  _subModules.insert(std::make_pair(ID_INPUT_MANAGER, std::make_unique<InputManager>(*this, _pOwningEngineContext.get())));
  _subModules.insert(std::make_pair(ID_NETWORK_MANAGER, std::make_unique<NetworkManager>(*this, _pOwningEngineContext.get())));
  _subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_unique<LogicManager>(*this, _pOwningEngineContext.get())));
  _subModules.insert(std::make_pair(ID_SIMULATION_MANAGER, std::make_unique<SimulationManager>(*this, _pOwningEngineContext.get())));
  _subModules.insert(std::make_pair(ID_OUTPUT_MANAGER, std::make_unique<OutputManager>(*this, _pOwningEngineContext.get())));

  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::Success, "Engine instance created.");
}

Engine::~Engine() noexcept
{
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "Engine instance destroyed.");
}

bool Engine::Initialize()
{
  // Call initialize on all submodules.
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    // Initialize module.
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif

  }

  // Set Engine module state to Idle.
  SetModuleState(eModuleState::OK);
  return true;
}

Scene* Engine::AddScene(Window* pTargetWindow, size_t sceneId)
{
  return SCENE_MANAGER->CreateScene(_pEngineContext, this, pTargetWindow, sceneId);
}

Window* Engine::AddWindow()
{
  // Instantiate new Window
  Window* pNewWindow = OUTPUT_MANAGER->ConstructWindow(
    eWindowType::MAIN_GAME_WINDOW, 
    WORLD_GAME_NAME, 
    GAME_WINDOW_DEFAULT_WIDTH, 
    GAME_WINDOW_DEFAULT_HEIGHT
  );

  // Attach it to Engine
  AttachWindow(pNewWindow);

  return pNewWindow;
}

bool Engine::RemoveWindow(Window* pWindow)
{
  // Detach it to Engine
  DetachWindow(pWindow);

  // Destruct it
  OUTPUT_MANAGER->DestroyWindow(pWindow);

  return true;
}

bool Engine::InitializeSceneInModules(Scene* pScene)
{
  bool result = true;

  // Initialize scene instance in all modules
  result = result && SCENE_MANAGER->InitializeScene(pScene);
  result = result && INPUT_MANAGER->InitializeScene(pScene);
  result = result && NETWORK_MANAGER->InitializeScene(pScene);
  result = result && LOGIC_MANAGER->InitializeScene(pScene);
  result = result && SIMULATION_MANAGER->InitializeScene(pScene);
  result = result && OUTPUT_MANAGER->InitializeScene(pScene);

  // If something failed
  if (!result)
  {
    PUSH_ENGINE_ERROR(eEngineError::SceneInitializationFailed, "Scene initialization failed", "");
  }
 
  return true;
  
}

bool Engine::Run()
{
  // If engine not initialized yet, do it so
  if (GetModuleState() == eModuleState::Null)
  {
    Initialize();
  }

  // Create main Window instance
  Window* pMainWindow = this->AddWindow();
  // If creating Window failed
  if (pMainWindow == nullptr)
  {
    return false;
  }

  // Create new Scene instance
  Scene* pScene = this->AddScene(pMainWindow, 0ULL);
  // If creating Scene failed
  if (pScene == nullptr)
  {
    return false;
  }

  // Initialize Scene instance everywhere
  if (!InitializeSceneInModules(pScene))
  {
    // TODO: Try to solve this situation during runtime
    return false;
  }

  // Construct initial scene
  // TODO: Make Scene method for loading from script file
  SCENE_MANAGER->LoadInitialScene(pScene);

  // TODO: Implement with TimeManager class
  auto prev = std::chrono::high_resolution_clock::now();
  dfloat deltaTime = 0.0f;

  // Main game loop.
  while (_pEngineContext->ShouldRun())
  {
    // TODO: Implement in TimeStamp class.
    // Get delta time.
    deltaTime = static_cast<dfloat>(std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::now() - prev
     ).count()) / 1000000;
    // Save now time for next frame calculation.
    prev = std::chrono::high_resolution_clock::now();
    // TODO: Implement in TimeStamp class.

    // Do ImGUI stuff.
    ProcessImGui();

    // Main frame pipeline.
    ProcessFrame(deltaTime, pScene, pMainWindow);
  }

  // Send Command to terminate Editor
  ENGINE_API->PushEditorCommand(eCommandType::Terminate);

  // Terminate self
  if (!Terminate())
  {
    SetModuleState(eModuleState::Error);
    return false;
  }
  return true;
}

bool Engine::AttachScene(Scene* pScene)
{
  auto result = _scenes.insert(std::make_pair(pScene->GetGuid(), pScene));

  return result.second;
}

bool Engine::DetachScene(Scene* pScene)
{
  auto result = _scenes.erase(pScene->GetGuid());

  return (result > 0);
}

bool Engine::AttachWindow(Window* pWindow)
{
  auto result = _windows.insert(std::make_pair(pWindow->GetGuid(), pWindow));

  return result.second;
}

bool Engine::DetachWindow(Window* pWindow)
{
  auto result = _windows.erase(pWindow->GetGuid());

  return (result > 0);
}

void Engine::ProcessImGui()
{
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Start the Dear ImGui frame
  ImGuiOpenGlWrapperNewFrame();
  ImGuiWrapper_NewFrame();
  ImGui::NewFrame();

  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window)
  {
    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }
}

bool Engine::Terminate()
{
  // Terminate all modules
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    if (!(*it).second->Terminate())
    {
      SetModuleState(eModuleState::Error);
      DLog(eLogType::Error, "Terminating main modules failed.");
      return false;
    }
  }

  // Terminate self

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "Engine instance terminated.");
  return true;
}

void Engine::ProcessFrame(dfloat deltaTime, Scene* pScene, Window* pMainWindow)
{
  ENGINE_API->ProcessEngineQueue();

  SCENE_MANAGER->ProcessScene(deltaTime, pScene);
  INPUT_MANAGER->ProcessScene(deltaTime, pScene);
  NETWORK_MANAGER->ProcessScene(deltaTime, pScene);
  LOGIC_MANAGER->ProcessScene(deltaTime, pScene);
  SIMULATION_MANAGER->ProcessScene(deltaTime, pScene);
  OUTPUT_MANAGER->ProcessScene(deltaTime, pScene, pMainWindow);

  // Process all warnings, errors and critical errors that has occured during this frame and handle them.
  CheckModuleStates();
}

void Engine::CheckModuleStates()
{
  // TODO: Implement.
}

EngineApi* Engine::GetEngineApiPtr() const
{
  return static_cast<EngineApi*>(_subModules.find(ID_ENGINE_API)->second.get());
}
