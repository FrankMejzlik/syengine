
/*!
 * \file
 * \breif Entry point for this engine
 */


// Requirement for StbImage loader
#define STB_IMAGE_IMPLEMENTATION

// Tell ImGUI we're using GLEW OpenGL loader
#define IMGUI_IMPL_OPENGL_LOADER_GLEW


#include <thread>
#include <iostream>

#include "Instance.h"
#include "Engine.h"

#if EXPORT_ENGINE_API
  #include "export.h"
#endif

#if RUN_MAIN_TESTS
  #include "TEST_main.h"
#endif

using namespace SYE;


int main([[maybe_unused]] int argc, [[maybe_unused]]char** argv)
{  
#if RUN_MAIN_TESTS
  TEST_MathLibrary();
#endif

#if TARGET_WINDOWS
  #if DEV && _DEBUG

    // Show memory leak dump after application exit
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  #endif
#endif // TARGET_WINDOWS
  {

    // Start with instantiating ProcessInstance 
    ProcessInstance processInstance;

  #if TEST_EXPORTED_FUNCTIONS
    std::thread tTest(&TEST_APIFns);
  #endif

    // Prepare Engine for startup
    Engine engine(&processInstance);

    // Run engine
    engine.Run();

  #if TEST_EXPORTED_FUNCTIONS
    tTest.join();
  #endif

    // Do final cleanup
    processInstance.Cleanup();
  }

  return 0;
}
