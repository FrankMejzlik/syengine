
#include "SceneManager.h"

#include "Camera.h"
#include "ScriptHandler.h"

#include "script_includes.h"

Scene* SceneManager::_pActiveScene = nullptr;

Scene* SceneManager::GetActiveScene()
{
  return _pActiveScene;
}

SceneManager::SceneManager(BaseModule& parentModule) noexcept:
  BaseModule(parentModule)
{
  _subModules.insert(std::make_pair(ID_ENTITY_MANAGER, std::make_unique<EntityManager>(*this)));

  DLog(eLogType::Success, "SceneManager instance created.");
}

SceneManager::~SceneManager()
{
  // If instance not terminated, do so.
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }
  
  DLog(eLogType::Success, "SceneManager instance destroyed.");
}

bool SceneManager::Initialize()
{
  // Initialize submodules.
  for (std::map< int, std::unique_ptr<BaseModule> >::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }


  // Class specific initialization


  SetModuleState(eModuleState::OK);

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

Scene* SceneManager::CreateScene(Window* pWindow)
{
  // Construct new scene instance.
  std::unique_ptr<Scene> pNewScene;

  try
  {
    pNewScene = std::make_unique<Scene>(ENTITY_MANAGER);
  }
  catch (const std::bad_alloc&)
  {
    // Unrecovarable error - just safe terminate as soon as possible.
    SetModuleState(eModuleState::CriticalError);
  }

  // If instantiation failed.
  if (!pNewScene)
  {
    DLog(eLogType::Info, "Failed creating scene.");
    return nullptr;
  }

  // Attach to Window instance
  pNewScene->SetMainWindowPtr(pWindow);

  DLog(eLogType::Success, "Created scene.");

  return InsertScene(std::move(pNewScene));
}

Scene* SceneManager::LoadInitialScene(Scene* pNewScene)
{
  DLog(eLogType::Info, "Loading initial test scene.");

  // Create Camera 
  Entity* pCameraEntity = pNewScene->CreateCamera(
    Vector3f(10.0f, 10.0f, 10.0f),
    Vector3f(0.0f, 1.0f, 0.0f),
    4.0f, -0.8f,
    true
  );
  // Add ScriptHanlder Component
  ScriptHandler* pScriptHander = pCameraEntity->AddComponent<ScriptHandler>();
  // Attach specific script to it
  pScriptHander->AddScript<FirstPersonCameraController>();

  // Floor
  pNewScene->CreateBlock(
    Vector3f(0.0f, -20.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    100.0f, 1.0f, 100.0f,
    true
  );


  for (size_t i = 0; i < 10; ++i)
  {
    for (size_t j = 0; j < 10; ++j)
    {
      pNewScene->CreateBlock(
        Vector3f(-5.0f + (float)i, 10.0f, -10.0f + (float)j), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
        1.0f, 1.0f, 1.0f,
        true, 1.0f
      );
    }
  }
  pNewScene->CreateBlock(
    Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    5.0f, 5.0f, 5.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(1.0f, 11.0f, 1.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    4.0f, 1.0f, 2.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(0.0f, -2.0f, 0.0f), Vector3f(0.0f, 2.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    2.0f, 8.0f, 5.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(2.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(-2.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(0.0f, 2.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(10.0f, -2.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(12.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(-12.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    true, 1.0f
  );

  pNewScene->CreateBlock(
    Vector3f(10.0f, 2.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    true, 1.0f
  );

  // Create Quad
  /*pNewScene->CreateQuad(
    Vector3f(0.0f, -10.0f, 0.0f), Vector3f(90.0f* (float)DEG_TO_RAD, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
    20.0f, 20.0f, 
    true
  );*/
    
  // Create DirectionalLight
  pNewScene->CreateDirectionalLight(
    Vector3f(0.0f, 0.0f, 0.0f),          // Position vector
    Vector3f(0.0f, 0.0f, 0.0f),          // rotation vector
    Vector3f(1.0f, 1.0f, 1.0f),          // scale vector

    Vector3f(1.0f, 1.0f, 1.0f),          // Colour vector
    Vector3f(0.1f, 0.5f, 0.1f),          // Intensities
    Vector3u(2048, 2048, 0),              // Shadow dimensions
    Vector3f(7.0f, -5.0f, 3.0f)
  ); 

  // Create PointLight
  pNewScene->CreatePointLight(
    Vector3f(5.0f, -5.0f, 5.0f),       // Position vector
    Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
    Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

    Vector3f(1.0f, 0.0f, 0.0f),        // Colour vector
    Vector3f(0.0f, 1.0f, 0.0f),        // Intensities
    Vector3u(2048, 2048, 0),            // Shadow dimensions
    0.01f, 100.0f,                     // Plane dimensions
    Vector3f(0.01f, 0.06f, 0.02f)      // Coefficients
  );

  // Create SpotLight
  pNewScene->CreateSpotLight(
    Vector3f(-6.0f, -4.0f, -6.0f),       // Position vector
    Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
    Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

    Vector3f(0.0f, 0.0f, 1.0f),        // Colour vector
    Vector3f(0.0f, 1.0f, 0.0f),        // Intensities
    Vector3u(2048, 2048, 0),  // Shadow dimensions
    0.01f, 100.0f,           // Plane dimensions
    Vector3f(0.01f, 0.06f, 0.02f),      // Coefficients

    Vector3f(1.0f, -1.0f, 1.0f),      // Light direction
    20.0f                                // Cone angle (degrees)
  );

  
  /*pNewScene->CreateStaticModelFromFile(
    "terrain",
    glm::vec3(-00.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(1.1f, 1.1f, 1.1f),
    "Resource/models/SnowTerrain.obj"
  );

  pNewScene->CreateStaticModelFromFile(
    "model1",
    glm::vec3(-6.0f, 6.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(.1f, .1f, 0.1f),
    "Resource/panFazulka.DAE"
  );*/

  _pActiveScene = pNewScene;

  DLog(eLogType::Success, "Initial test scene loaded.");

  return pNewScene;
}

Scene* SceneManager::InsertScene(std::unique_ptr<Scene>&& sceneToInsert)
{
  auto result = _scenes.insert(make_pair(sceneToInsert->GetGuid(), std::move(sceneToInsert)));

  // If tried to insert already present scene.
  if (result.second == false)
  {
    SetModuleState(eModuleState::Warning);
    PushWarning(eModuleWarning::kDuplicateEntries, "Tried to insert already present Scene instance.");

    DLog(eLogType::Warning, "Tried to insert already present Scene instance.");
    assert(result.second == true);
  }

  // Set it as active.
  _pActiveScene = &(*(result.first->second));

  return &(*(result.first->second));
}

const Scene* SceneManager::GetSceneConstPtr(size_t sceneGuid) const
{
  return _scenes.find(sceneGuid)->second.get();
}

Scene* SceneManager::GetScenePtr(size_t sceneGuid)
{
  return _scenes[sceneGuid].get();
}

void SceneManager::HandleInput(Scene* pScene)
{
  InputManager* pInputManager = pScene->GetInputManagerPtr();
  Camera* pCamera = pScene->GetEditorCamera();

  // If Mouse Right button pressed
  if (pInputManager->IsOnKeyboardMouseDown(INPUT_MOUSE_BUTTON_RIGHT))
  {
    // Shoot box
    pScene->ShootBox(
      pCamera->GetCameraPosition(), 
      pCamera->GetPickingRay(
        pInputManager->GetMouseXPos(), 
        pInputManager->GetMouseYPos()
      )
    );
  }
  else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F2))
  {
    
  }
}

void SceneManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{
  UNREFERENCED_PARAMETER(deltaTime);
  UNREFERENCED_PARAMETER(pScene);

  HandleInput(pScene);

  // TODO:
}