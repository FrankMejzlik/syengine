
#include "Engine.h"

using namespace WeSp;

Engine::Engine(Instance* pInstance) :
  BaseModule(MAGIC_BASE_MODULE_NUMBER), // Identify as root module
  _pInstance(pInstance),
  globObjID(0)
{
  /*
    Whatever modules are pushed into _subModules hasp map are loaded and initialized.
  */
#if RUN_ENGINE_API

  // Insert EngineAPI instance
  _subModules.insert(std::make_pair(ID_ENGINE_API, std::make_shared<EngineApi>(*this)));
  // Set engine pointer to this.
  SetEngineApiPointer(std::static_pointer_cast<EngineApi>(_subModules.find(ID_ENGINE_API)->second).get());

#endif

  _subModules.insert(std::make_pair(ID_SCENE_MANAGER, std::make_shared<SceneManager>(*this)));
  _subModules.insert(std::make_pair(ID_INPUT_MANAGER, std::make_shared<InputManager>(*this)));
  _subModules.insert(std::make_pair(ID_NETWORK_MANAGER, std::make_shared<NetworkManager>(*this)));
  _subModules.insert(std::make_pair(ID_SIMULATION_MANAGER, std::make_shared<SimulationManager>(*this)));
  _subModules.insert(std::make_pair(ID_OUTPUT_MANAGER, std::make_shared<OutputManager>(*this)));

  DLog(eLogType::Success, "Engine instance created.");
}

Engine::~Engine()
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
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    // Initialize module.
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif

  }

  // Set Engine module state to Idle.
  SetModuleState(eModuleState::Idle);
  return true;
}



bool Engine::Run()
{
  // If engine not initialized yet, do it so
  if (GetModuleState() == eModuleState::Null)
  {
    Initialize();
  }

#if 0
  // Create all output channels.
  std::shared_ptr<Window> pMainWindow = OUTPUT_MANAGER->ConstructWindow(eWindowType::MAIN_GAME_WINDOW, WORLD_GAME_NAME, GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);

  
  // Construct initial scene.
  SCENE_MANAGER->LoadInitialScene();

  // Main game loop.
  while (_engineContext.GetBShouldRun())
  {




    pMainWindow->SwapBuffers();

  }


  //// vvvvvvvvvvvvvvvvvv to ref vvvvvvvvvvvvvvvvvvvvvvv
#endif
#if 1

  std::shared_ptr<Window> pMainWindow = OUTPUT_MANAGER->ConstructWindow(eWindowType::MAIN_GAME_WINDOW, WORLD_GAME_NAME, GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);

  //Window mainWindow(GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);
  pMainWindow->Initialize();

  CreateObjects();
  CreateShaders();

  camera = Camera(glm::vec3(-1.0f, -0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 1.0f);

  brickTexture = Texture("Resource/textures/brick.png");
  dirtTexture = Texture("Resource/textures/dirt.png");
  plainTexture = Texture("Resource/textures/plain.png");

  brickTexture.LoadTexture();
  dirtTexture.LoadTexture();
  plainTexture.LoadTexture();

  xwing = Model();
  xwing.LoadModelFromFile("Resource/models/x-wing.obj");

  blackhawk = Model();
  blackhawk.LoadModelFromFile("Resource/models/uh60.obj");

  dude2 = Model();
  dude2.LoadModelFromFile("Resource/panFazulka.DAE");

  dude = SkeletalModel();
  dude.LoadModelFromFile("Resource/boblampclean.md5mesh");

  wolf = SkeletalModel();
  wolf.LoadModelFromFile("Resource/Wolf_dae.dae");

  plane = SkeletalModel();
  plane.LoadModelFromFile("Resource/Wolf_dae.dae");
  

  {
    mainLight = DirectionalLight(
      glm::vec3(0.0f, 0.0f, 0.0f),          // Position vector
      glm::vec3(0.0f, 0.0f, 0.0f),          // rotation vector
      glm::vec3(1.0f, 1.0f, 1.0f),          // scale vector

      glm::vec3(1.0f, 1.0f, 1.0f),          // Colour vector
      glm::vec3(0.0f, 0.9f, 0.0f),          // Intensities
      glm::vec3(2048.0f, 2048.0f, 0.0f),    // Shadow dimensions
      glm::vec3(-10.0f, -12.0f, 18.5f)      // Light direction vector
    );

    pointLights[0] = PointLight(           
      glm::vec3(3.0f, 2.0f, 5.0f),        // Position vector
      glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
      glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

      glm::vec3(0.0f, 0.0f, 1.0f),        // Colour vector
      glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
      glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
      glm::vec2(0.01f, 100.0f),           // Plane dimensions
      glm::vec3(0.08f, 0.05f, 0.02f)      // Coefficients
    );
    ++pointLightCount;

    pointLights[1] = PointLight(
      glm::vec3(-3.0f, 2.0f, 5.0f),       // Position vector
      glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
      glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

      glm::vec3(0.0f, 1.0f, 0.0f),        // Colour vector
      glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
      glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
      glm::vec2(0.01f, 100.0f),           // Plane dimensions
      glm::vec3(0.08f, 0.05f, 0.02f)      // Coefficients
    );
    ++pointLightCount;

    pointLights[2] = PointLight(
      glm::vec3(0.0f, 2.0f, -5.0f),       // Position vector
      glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
      glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

      glm::vec3(1.0f, 0.0f, 0.0f),        // Colour vector
      glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
      glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
      glm::vec2(0.01f, 100.0f),           // Plane dimensions
      glm::vec3(0.08f, 0.05f, 0.02f)      // Coefficients
    );
    //++pointLightCount;


    spotLights[0] = SpotLight(
      glm::vec3(2.5f, 2.0f, -5.0f),       // Position vector
      glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
      glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

      glm::vec3(1.0f, 1.0f, 1.0f),        // Colour vector
      glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
      glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
      glm::vec2(0.01f, 100.0f),           // Plane dimensions
      glm::vec3(0.08f, 0.05f, 0.02f),      // Coefficients

      glm::vec3(-1.0f, -1.0f, -1.0f),      // Light direction
      20.0f                                // Cone angle (degrees)
    );
    ++spotLightCount;


    spotLights[1] = SpotLight(
      glm::vec3(2.5f, 2.0f, -5.0f),       // Position vector
      glm::vec3(0.0f, 0.0f, 0.0f),        // rotation vector
      glm::vec3(1.0f, 1.0f, 1.0f),        // scale vector

      glm::vec3(0.0f, 1.0f, 0.0f),        // Colour vector
      glm::vec3(0.0f, 1.0f, 0.0f),        // Intensities
      glm::vec3(2048.0f, 2048.0f, 0.0f),  // Shadow dimensions
      glm::vec2(0.01f, 100.0f),           // Plane dimensions
      glm::vec3(0.08f, 0.05f, 0.02f),      // Coefficients

      glm::vec3(0.0f, 5.0f, -1.0f),      // Light direction
      30.0f                                 // Cone angle (degrees)
    );
    ++spotLightCount;
  }

  // Order matters!
  std::vector<std::string> skyboxFaces;
  skyboxFaces.push_back("Resource/textures/skybox/cupertin-lake_rt.tga");
  skyboxFaces.push_back("Resource/textures/skybox/cupertin-lake_lf.tga");
  skyboxFaces.push_back("Resource/textures/skybox/cupertin-lake_up.tga");
  skyboxFaces.push_back("Resource/textures/skybox/cupertin-lake_dn.tga");
  skyboxFaces.push_back("Resource/textures/skybox/cupertin-lake_bk.tga");
  skyboxFaces.push_back("Resource/textures/skybox/cupertin-lake_ft.tga");


  // Instantiate skybox
  skybox = Skybox(skyboxFaces);

  GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
    uniformSpecularIntensity = 0, uniformShininess = 0;

  // Get projeciton matrix
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)(pMainWindow->GetBufferWidth()) / pMainWindow->GetBufferHeight(), 0.1f, 100.0f);

  double frameTimer = 0;
  float toAngle = 0;
  // Loop until window is closed

  while (_engineContext.GetBShouldRun())
  {
    // Timing
    GLfloat now = static_cast<GLfloat>(glfwGetTime());
    deltaTime = now - lastTime;
    lastTime = now;

    // Get and handle user input events
    glfwPollEvents();
    camera.KeyControl(pMainWindow->GetKeys(), deltaTime);
    camera.MouseControl(pMainWindow->GetXChange(), pMainWindow->GetYChange());


    if (pMainWindow->GetKeys()[GLFW_KEY_L])
    {
      pointLights[0].TogglePoint();
      pointLights[1].TogglePoint();
      pointLights[2].TogglePoint();
      pMainWindow->GetKeys()[GLFW_KEY_L] = false;
    }

    if (pMainWindow->GetKeys()[GLFW_KEY_K])
    {
      spotLights[0].ToggleSpot();
      pMainWindow->GetKeys()[GLFW_KEY_K] = false;
    }

    ENGINE_API->ProcessEngineQueue();

    // Calculate directional light shadow maps
    DirectionalShadowMapPass(&mainLight);

    // Calculate point light shadow maps
    for (size_t i = 0; i < pointLightCount; ++i)
    {
      OmniShadowMapPass(&pointLights[i]);
    }

    // Calculate spot light shadow maps
    for (size_t i = 0; i < spotLightCount; ++i)
    {
      OmniShadowMapPass(&spotLights[i]);
    }

    // Render actual scene with computed shadow maps
    RenderPass(camera.CalculateViewMatrix(), projection);

    pMainWindow->SwapBuffers();
  }
#endif
  // OpenGL windows closed

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

bool Engine::Terminate()
{
  // Terminate all modules
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
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

std::shared_ptr<EngineApi> Engine::GetEngineAPI()
{
  return ENGINE_API;
}
