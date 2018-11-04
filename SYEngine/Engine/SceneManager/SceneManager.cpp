
#include "SceneManager.h"


Scene* SceneManager::_pActiveScene = nullptr;

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
    std::string("main_camera"), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -120.0f, -45.0f
  );

  /*pNewScene->CreateQuad(
    std::string("main_floor"), glm::vec3(0.0f, -0.0f, -0.0f), glm::vec3(90.0f * DEG_TO_RAD, 00.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
    10.0f, 10.0f
  );
  pNewScene->CreateQuad(
    std::string("main_floor"), glm::vec3(0.0f, -0.0f, -0.0f), glm::vec3(-90.0f * DEG_TO_RAD, 00.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
    10.0f, 10.0f
  );

  pNewScene->CreateQuad(
    std::string("main_floor"), glm::vec3(0.0f, -0.0f, 0.0f), glm::vec3(0.0f, 90.0f * DEG_TO_RAD, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
    10.0f, 10.0f
  );
  pNewScene->CreateQuad(
    std::string("main_floor"), glm::vec3(0.0f, -0.0f, 0.0f), glm::vec3(0.0f, -90.0f * DEG_TO_RAD, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
    10.0f, 10.0f
  );

  pNewScene->CreateQuad(
    std::string("main_floor"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f * DEG_TO_RAD), glm::vec3(1.0f, 1.0f, 1.0f),
    10.0f, 10.0f
  ); 
  pNewScene->CreateQuad(
    std::string("main_floor"), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(180.0f * DEG_TO_RAD, 0.0f, -90.0f * DEG_TO_RAD), glm::vec3(1.0f, 1.0f, 1.0f),
    10.0f, 10.0f
  ); */
  

  auto block0 = pNewScene->CreateBlock(
    std::string("floor1"), glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(1.0f, 1.0f, 1.0f),
    100.0f, 2.0f, 100.0f, 
    true // Is  static
  );

  auto block1 = pNewScene->CreateBlock(
    std::string("block1"), glm::vec3(3.0f, 3.0f, 3.1f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(1.0f, 1.0f, 1.0f),
    2.0f, 2.0f, 2.0f,
    true // Is not static
  );

  auto block2 = pNewScene->CreateBlock(
    std::string("block2"), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(1.0f, 1.0f, 1.0f),
    2.0f, 2.0f, 2.0f,
    false // Is not static
  );

  //for (int i = -100; i < 100; i = i + 5)
  //{
  //  for (int j = -100; j < 100; j = j + 5)
  //  {
  //    pNewScene->CreateBlock(
  //      std::string("block2"), glm::vec3(i, 10.0f, j), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(1.0f, 1.0f, 1.0f),
  //      2.0f, 2.0f, 2.0f,
  //      false // Is not static
  //    );
  //  }
  //}

  pNewScene->CreateStaticModelFromFile(
    "terrain",
    glm::vec3(-00.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(1.1f, 1.1f, 1.1f),
    "Resource/models/SnowTerrain.obj"
  );

  pNewScene->CreateStaticModelFromFile(
    "model1",
    glm::vec3(-6.0f, 6.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(.1f, .1f, 0.1f),
    "Resource/panFazulka.DAE"
  );


  // Create main DirectionalLight.
  pNewScene->CreateDirectionalLight(
    "main_light",
    glm::vec3(0.0f, 0.0f, 0.0f),          // Position vector
    glm::vec3(0.0f, 0.0f, 0.0f),          // rotation vector
    glm::vec3(1.0f, 1.0f, 1.0f),          // scale vector

    glm::vec3(1.0f, 1.0f, 1.0f),          // Colour vector
    glm::vec3(0.1f, 0.5f, 0.0f),          // Intensities
    glm::vec3(2048.0f, 2048.0f, 0.0f),    // Shadow dimensions
    glm::vec3(10.0f, -10.0f, 10.0f)
  );

  // Create  PointLight.
  pNewScene->CreatePointLight(
    "point_light_001",
    glm::vec3(1.0f, 2.0f, -5.0f),       // Position vector
    glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
    glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

    glm::vec3(1.0f, 0.0f, 0.0f),        // Colour vector
    glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
    glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
    glm::vec2(0.01f, 100.0f),           // Plane dimensions
    glm::vec3(0.08f, 0.06f, 0.04f)      // Coefficients
  );

  // Create  PointLight.
  pNewScene->CreatePointLight(
    "point_light_001",
    glm::vec3(-6.0f, 2.0f, 0.0f),       // Position vector
    glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
    glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

    glm::vec3(0.0f, 1.0f, 0.0f),        // Colour vector
    glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
    glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
    glm::vec2(0.01f, 100.0f),           // Plane dimensions
    glm::vec3(0.08f, 0.06f, 0.04f)      // Coefficients
  );

  // Create  PointLight.
  pNewScene->CreatePointLight(
    "point_light_001",
    glm::vec3(0.0f, 2.0f, 6.0f),       // Position vector
    glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
    glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

    glm::vec3(0.0f, 0.0f, 1.0f),        // Colour vector
    glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
    glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
    glm::vec2(0.01f, 100.0f),           // Plane dimensions
    glm::vec3(0.08f, 0.06f, 0.04f)      // Coefficients
  );

  // Create  SpotLight.
  pNewScene->CreateSpotLight(
    "spot_light_001",
    glm::vec3(8.0f, 9.0f, 9.0f),       // Position vector
    glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
    glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

    glm::vec3(0.0f, 1.0f, 1.0f),        // Colour vector
    glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
    glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
    glm::vec2(0.01f, 100.0f),           // Plane dimensions
    glm::vec3(0.04f, 0.03f, 0.01f),      // Coefficients

    glm::vec3(-1.0f, -1.0f, -1.0f),      // Light direction
    20.0f                                // Cone angle (degrees)
  );

  // Create  SpotLight.
  pNewScene->CreateSpotLight(
    "spot_light_001",
    glm::vec3(-6.0f, 6.0f, -6.0f),       // Position vector
    glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
    glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

    glm::vec3(1.0f, 1.0f, 0.0f),        // Colour vector
    glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
    glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
    glm::vec2(0.01f, 100.0f),           // Plane dimensions
    glm::vec3(0.08f, 0.06f, 0.04f),      // Coefficients

    glm::vec3(1.0f, -1.0f, 1.0f),      // Light direction
    20.0f                                // Cone angle (degrees)
  );


  _pActiveScene = pNewScene.get();

  DLog(eLogType::Success, "Initial test scene loaded.");
  return pNewScene;
}

Scene* SceneManager::GetActiveScene()
{
  return _pActiveScene;
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