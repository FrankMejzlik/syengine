

#include "memory_diagnostics.h"

#include <thread>

#include "IUncopyable.h"
#include "Instance.h"
#include "Editor.h"
#include "Engine.h"

using namespace WeSp;

void RunEditor(WeSp::Instance* instance, int argc, char** argv, std::shared_ptr<EngineApi> pEngineAPI)
{
  wxApp::SetInstance(new Editor(instance, pEngineAPI));
  wxEntryStart(argc, argv);
  wxTheApp->OnInit();
  wxTheApp->OnRun();
  wxTheApp->OnExit(); 
  return;
}

int main(int argc, char** argv)
{
  // Show memory leak dump after application exit
#if DEV && _DEBUG
  _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );  
#endif

  // Start with instantiating instance instance :D 
  Instance instance;

  // Create Egine instance and prepare it for run in thread
  Engine engine(&instance);
  engine.Initialize();
  std::thread tEngine(&Engine::Run, &engine);

  // Run Editor
  std::thread tEditor(RunEditor, &instance, argc, argv, engine.GetEngineAPI());
     
  // Wait for threads to complete
  if (tEditor.joinable())
  {
    tEditor.join();
  }
  if (tEngine.joinable())
  {
    tEngine.join();
  }
  
  // Do fial cleanup
  instance.Cleanup();

  return 0;
}
