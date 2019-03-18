#pragma once

#include <stdint.h>

#include "common.h"
#include "Engine.h"

extern "C"
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}


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
    data.push_back(static_cast<dfloat>(posX));
    data.push_back(static_cast<dfloat>(posY));
    data.push_back(static_cast<dfloat>(posZ));
    data.push_back(static_cast<dfloat>(rotX));
    data.push_back(static_cast<dfloat>(rotY));
    data.push_back(static_cast<dfloat>(rotZ));
    data.push_back(static_cast<dfloat>(scaleX));
    data.push_back(static_cast<dfloat>(scaleY));
    data.push_back(static_cast<dfloat>(scaleZ));
    data.push_back(static_cast<dfloat>(width));
    data.push_back(static_cast<dfloat>(height));
    data.push_back(static_cast<dfloat>(length));


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

    return 0;
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
    data.push_back(static_cast<dfloat>(posX));
    data.push_back(static_cast<dfloat>(posY));
    data.push_back(static_cast<dfloat>(posZ));
    data.push_back(static_cast<dfloat>(rotX));
    data.push_back(static_cast<dfloat>(rotY));
    data.push_back(static_cast<dfloat>(rotZ));
    data.push_back(static_cast<dfloat>(scaleX));
    data.push_back(static_cast<dfloat>(scaleY));
    data.push_back(static_cast<dfloat>(scaleZ));

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

    return 0;
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