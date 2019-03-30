
#include "SceneManager.h"

#include "Camera.h"
#include "ScriptHandler.h"
#include "Script.h"

#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "Mesh.h"

// Build initial scene in this script's SetupScene method
#include "_SceneBuilder.h"

Scene* SceneManager::_pActiveScene = nullptr;

Scene* SceneManager::GetActiveScene()
{
  return _pActiveScene;
}

SceneManager::SceneManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  _subModules.insert(std::make_pair(ID_ENTITY_MANAGER, std::make_unique<EntityManager>(*this, _pEngineContext)));

  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::cSuccess, "SceneManager instance created.");
}

SceneManager::~SceneManager()
{
  // If instance not terminated, do so.
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }
  
  DLog(eLogType::cSuccess, "SceneManager instance destroyed.");
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

  DLog(eLogType::cSuccess, "SceneManager instance initialized.");
  return true;
}

bool SceneManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::cSuccess, "SceneManager instance terminated.");
  return true;  
}

Scene* SceneManager::CreateScene(EngineContext* pEngineContext, Engine* pOwnerEngine, Window* pWindow, size_t sceneId)
{
  // Construct new scene instance.
  std::unique_ptr<Scene> pScene;

  try
  {
    pScene = std::make_unique<Scene>(pEngineContext, pOwnerEngine, pWindow, sceneId);
  }
  catch (const std::bad_alloc&)
  {
    // Unrecovarable error - just safe terminate as soon as possible.
    SetModuleState(eModuleState::CriticalError);
  }

  // If instantiation failed.
  if (!pScene)
  {
    DLog(eLogType::cInfo, "Failed creating scene.");
    return nullptr;
  }

  // Attach to Window instance
  pScene->SetMainWindowPtr(pWindow);

  DLog(eLogType::cSuccess, "Created scene.");

  return InsertScene(std::move(pScene));
}

Scene* SceneManager::LoadInitialScene(Scene* pScene)
{
  DLog(eLogType::cInfo, "Loading initial test scene.");


  // Call special SceneBuilder script
  _SceneBuilder sceneBuilder;
  sceneBuilder.SetupScene(pScene);

  /* Create special system components
      NOTE: If system Entities added after normal ones, they will be executed
            after them and you don't get one frame delay in calculations. */
  SetupSystemEntities(pScene);

  
  /*pScene->CreateStaticModelFromFile(
    "terrain",
    glm::vec3(-00.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(1.1f, 1.1f, 1.1f),
    "Resource/models/SnowTerrain.obj"
  );

  pScene->CreateStaticModelFromFile(
    "model1",
    glm::vec3(-6.0f, 6.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f * DEG_TO_RAD), glm::vec3(.1f, .1f, 0.1f),
    "Resource/panFazulka.DAE"
  );*/

  _pActiveScene = pScene;

  DLog(eLogType::cSuccess, "Initial test scene loaded.");

  return pScene;
}

bool SceneManager::SetupSystemEntities(Scene* pScene)
{

#if RENDER_SCENE_TO_TEXTUE

  ///////////////////////////////
  // Setup primitive to draw scene texture to
  ///////////////////////////////

  // Create new Entity
  Entity* pRenderToEntity = pScene->GetEntityManagerPtr()->CreateEntity<Entity>(pScene);

  // Register this Entity as special to Scene.
  pScene->RegisterSystemEntity(RENDER_ONTO_ENTITY, pRenderToEntity);

  // Add Transform Component
  Transform* pTransform = pRenderToEntity->AddComponent<Transform>();
  pTransform->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
  pTransform->SetRotation(Vector3f(0.0f, 0.0f, 0.0f));
  pTransform->SetScale(Vector3f(1.0f, 1.0f, 1.0f));

  // Add MeshRenderer Component
  MeshRenderer* pMeshRenderer = pRenderToEntity->AddComponent<MeshRenderer>();
  {
    Mesh* pMesh = pMeshRenderer->AddMesh();
    {
      pMesh->ClearMesh();
      pMesh->MakeQuad(RENDER_ONTO_ENTITY_WIDTH, RENDER_ONTO_ENTITY_HEIGHT);
    }

    // Create special render target texture
    Texture* pRenderTargetTextre = pScene->GetComponentManagerPtr()->CreateComponent<Texture>(pRenderToEntity);

    // Initialize zero data for framebuffer texture
    std::vector<std::byte> data;
    // Fill this vector with RGB float bytes
    data.resize(RENDER_TO_TEXTURE_WIDTH * RENDER_TO_TEXTURE_HEIGHT * sizeof(dfloat) * 3, std::byte(0));

    // Make this Texture work as framebuffer
    pRenderTargetTextre->InitTextresAsRenderTarget(data, GL_COLOR_ATTACHMENT0, RENDER_TO_TEXTURE_WIDTH, RENDER_TO_TEXTURE_HEIGHT);

    // Register this render target Texture
    pScene->RegisterRenderTargetTexture(0ULL, pRenderTargetTextre);

    // Add this special material
    pMeshRenderer->AddMaterial(pRenderTargetTextre, nullptr, nullptr);
    pMeshRenderer->AddMeshToMaterialIndex(0ULL, 0ULL);
  }
  // Unregister this MeshRenderer form standard rendering pipeline
  pScene->UnregisterComponent(pMeshRenderer);
  


  // Add Script for syncing position and rotation of projection Quad
  ScriptHandler* pScriptHandler = pRenderToEntity->AddComponent<ScriptHandler>();
  pScriptHandler->AddScript<LookAtQuad>();

  // Save all edits done on this Entity
  pRenderToEntity->SaveEntity();

#endif

  ///////////////////////////////
  // Setup utility Camera
  ///////////////////////////////

  Entity* pUtilityCamera = pScene->AddCamera(
    Vector3f(0.0f, 0.0f, 0.0f),      
    0.0f, 0.0f  
  );

  // Set pointer to this Camera to Scene
  pScene->SetUtilityCamera(pUtilityCamera->GetCameraPtr());

  return true;
}

Scene* SceneManager::InsertScene(std::unique_ptr<Scene>&& sceneToInsert)
{
  auto result = _scenes.insert(make_pair(sceneToInsert->GetGuid(), std::move(sceneToInsert)));

  // If tried to insert already present scene.
  if (result.second == false)
  {
    SetModuleState(eModuleState::Warning);
    PushWarning(eModuleWarning::kDuplicateEntries, "Tried to insert already present Scene instance.");

    DLog(eLogType::cWarning, "Tried to insert already present Scene instance.");
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
  Camera* pCamera = pScene->GetMainCamera();

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

void SceneManager::TerminateGame()
{
  // Terminate all Scenes
  _scenes.clear();
}

bool SceneManager::InitializeScene(Scene* pScene)
{
  UNREFERENCED_PARAMETER(pScene);

  return true;
}

void SceneManager::ProcessScene(dfloat deltaTime, Scene* pScene)
{
  UNREFERENCED_PARAMETER(deltaTime);
  UNREFERENCED_PARAMETER(pScene);

  HandleInput(pScene);

  // TODO:
}