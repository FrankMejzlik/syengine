
#include "SceneManager.h"

SceneManager::SceneManager(BaseModule &parentModule):
  BaseModule(parentModule)
{


  DLog(eLogType::Success, "SceneManager instance created.");
}

SceneManager::~SceneManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "SceneManager instance destroyed.");
}

std::shared_ptr<Scene> SceneManager::CreateScene(std::string sceneName)
{
  // Construct new scene.
  std::shared_ptr<Scene> pNewScene = std::make_shared<Scene>(sceneName);

  // If instantiation failed.
  if (!pNewScene)
  {
    DLog(eLogType::Info, "Failed creating '%s' scene.", sceneName.c_str());
    return nullptr;
  }

  // Insert it in hash map.
  _scenes.insert(std::make_pair(sceneName, pNewScene));

  DLog(eLogType::Success, "Created '%s' scene.", sceneName.c_str());
  return pNewScene;
}

std::shared_ptr<Scene> SceneManager::LoadInitialScene()
{
  DLog(eLogType::Info, "Loading initial test scene.");

  std::shared_ptr<Scene> pNewScene = CreateScene(std::string("initialScene"));

  // Insert test Entities into scene here.

  // Create main camera.
  pNewScene->CreateCamera(
    std::string("main_camera"), glm::vec3(-1.0f, -0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f
  );
  // Create main floor.
  pNewScene->CreateQuad(
    std::string("main_floor"), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
    10.0f, 10.0f
   );
  // Insert test Entities into scene here.

  DLog(eLogType::Success, "Initial test scene loaded.");
  return pNewScene;
}

bool SceneManager::Initialize()
{

  // Class specific initialization

  // Initialize submodules.
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "SceneManager instance initialized.");
  return true;
}

bool SceneManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "SceneManager instance terminated.");
  return true;
}