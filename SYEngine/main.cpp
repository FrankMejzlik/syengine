

#define STB_IMAGE_IMPLEMENTATION

#include "memory_diagnostics.h"

#include <thread>
#include <iostream>

#include "IUncopyable.h"
#include "Instance.h"
#include "Engine.h"

using namespace WeSp;


/**
* Exported functions to CS Editor wrapper.
*/
extern "C"
{

  __declspec(dllexport) uint64_t CALL_CONVENTION CreateBlock(
    double posX, double posY, double posZ,
    double rotX, double rotY, double rotZ,
    double scaleX, double scaleY, double scaleZ,
    double width, double height, double length
  )
  {

    Scene* pActiveScene = SceneManager::GetActiveScene();
    EngineApi* api = EngineApi::GetEngineApi();

    std::vector<float> data;
    data.push_back(posX);
    data.push_back(posY);
    data.push_back(posZ);
    data.push_back(rotX);
    data.push_back(rotY);
    data.push_back(rotZ);
    data.push_back(scaleX);
    data.push_back(scaleY);
    data.push_back(scaleZ);
    data.push_back(width);
    data.push_back(height);
    data.push_back(length);


    for (auto it : data)
    {
      std::cout << (it) << ", " << std::endl;
    }


    api->PushEngineCommand(eCommandType::CreateBlock, data);

    auto editorQueue = api->GetEditorCommandQueue();

    while (editorQueue->empty())
    {
      Sleep(15);
    }


    Command cmd = editorQueue->front();
    editorQueue->pop();

    if (cmd.GetType() == eCommandType::CreatedObjectId)
    {
      return cmd.GetUIntData()[0];
    }


  }

  __declspec(dllexport) uint64_t CALL_CONVENTION CreateStaticModelFromFile(
    double posX, double posY, double posZ,
    double rotX, double rotY, double rotZ,
    double scaleX, double scaleY, double scaleZ,
    const char filePath[2048]
  )
  {

    Scene* pActiveScene = SceneManager::GetActiveScene();
    EngineApi* api = EngineApi::GetEngineApi();

    std::vector<float> data;
    data.push_back(posX);
    data.push_back(posY);
    data.push_back(posZ);
    data.push_back(rotX);
    data.push_back(rotY);
    data.push_back(rotZ);
    data.push_back(scaleX);
    data.push_back(scaleY);
    data.push_back(scaleZ);

    std::vector<std::string> stringData;
    stringData.push_back(std::string(filePath));

    for (auto it : data)
    {
      std::cout << (it) << ", " <<  std::endl;
    }


    api->PushEngineCommand(eCommandType::CreateStaticModelFromFile, data, stringData);

    auto editorQueue = api->GetEditorCommandQueue();

    while (editorQueue->empty())
    {
      Sleep(15);
    }


    Command cmd = editorQueue->front();
    editorQueue->pop();

    if (cmd.GetType() == eCommandType::CreatedStaticModelFromFile)
    {
      return cmd.GetUIntData()[0];
    }


  }



  __declspec(dllexport) void CALL_CONVENTION RunEngine()
  {
    // Show memory leak dump after application exit
  #if DEV && _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  #endif

    // Start with instantiating instance instance :D 
    Instance instance;

    // Create Egine instance and prepare it for run in thread
    Engine engine(&instance);

    engine.Run();

    // Do fial cleanup
    instance.Cleanup();
  }

}



void TEST_APIFns()
{
  for (int i = 0; i < 10; ++i)
  {
    Sleep(5000);

    CreateStaticModelFromFile(
      0.0f + i, 0.0f + i, 0.0f + i,
      0.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 1.0f,
      "Resource\\textures\\Window.DAE"
    );

  }


}



int main(int argc, char** argv)
{
  // Show memory leak dump after application exit
#if DEV && _DEBUG
  _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );  
#endif

  // Start with instantiating instance instance :D 
  Instance instance;

  //std::thread tTest(&TEST_APIFns);


  // Create Egine instance and prepare it for run in thread
  Engine engine(&instance);
  
  engine.Run();
  
  //tTest.join();

  // Do fial cleanup
  instance.Cleanup();

  return 0;
}
