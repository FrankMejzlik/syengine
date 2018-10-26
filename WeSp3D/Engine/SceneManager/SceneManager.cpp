
#include "SceneManager.h"


SceneManager::SceneManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  
  _subModules.insert(std::make_pair(ID_ENTITY_MANAGER, std::make_shared<EntityManager>(*this)));

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
  // Construct new scene instance.
  std::shared_ptr<Scene> pNewScene = std::make_shared<Scene>(
    std::static_pointer_cast<EntityManager>(_subModules.find(ID_ENTITY_MANAGER)->second), 
    sceneName
  );

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

  pNewScene->CreateDirectionalLight(
    "main_light",
    glm::vec3(0.0f, 0.0f, 0.0f),          // Position vector
    glm::vec3(0.0f, 0.0f, 0.0f),          // rotation vector
    glm::vec3(1.0f, 1.0f, 1.0f),          // scale vector

    glm::vec3(1.0f, 1.0f, 1.0f),          // Colour vector
    glm::vec3(0.5f, 0.9f, 0.0f),          // Intensities
    glm::vec3(2048.0f, 2048.0f, 0.0f),    // Shadow dimensions
    glm::vec3(-10.0f, -12.0f, 18.5f)
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


void SceneManager::ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene)
{
  // TODO:
}