
#include "Engine.h"

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

bool Engine::Run()
{
  // If engine not initialized yet, do it so
  if (GetModuleState() == eModuleState::Null)
  {
    Initialize();
  }

  // Create all output channels.
  Window* pMainWindow = OUTPUT_MANAGER->ConstructWindow(
    eWindowType::MAIN_GAME_WINDOW, 
    WORLD_GAME_NAME, 
    GAME_WINDOW_DEFAULT_WIDTH, 
    GAME_WINDOW_DEFAULT_HEIGHT
  );

  // Create new Scene instance
  Scene* pScene = SCENE_MANAGER->CreateScene(pMainWindow);

  // Initialize LogicManager
  LOGIC_MANAGER->InitializeScene(pScene);

  // Set Scene's InputManager
  pScene->SetInputManagerPtr(INPUT_MANAGER);
  pScene->SetPhysicsManagerPtr(static_cast<PhysicsManager*>(SIMULATION_MANAGER->GetSubModulesRef()[ID_PHYSICS_MANAGER].get()));


  // Initialize physics.
  SIMULATION_MANAGER->InitializePhysicsScene(pScene);

  // Construct initial scene
  SCENE_MANAGER->LoadInitialScene(pScene);

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

SceneManager* Engine::GetSceneManagerPtr() const
{
  return static_cast<SceneManager*>(_subModules.find(ID_SCENE_MANAGER)->second.get());
}

