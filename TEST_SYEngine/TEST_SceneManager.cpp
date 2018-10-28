

#include "TEST_SceneManager.h"
//
//
//TEST_SceneManager::TEST_SceneManager():
//  instance(),
//  engine(&instance),
//  sceneManager(&engine)
//{}
//
//
//TEST_SceneManager::~TEST_SceneManager()
//{}
//
//bool TEST_SceneManager::RunAllTest()
//{
//  bool testsResult = true;
//
//  if (!TEST_CreateScene())
//  {
//    testsResult = false;
//  }
//
//  if (!TEST_CreateScene())
//  {
//    testsResult = false;
//  }
//  
//  return testsResult;
//}
//
//bool TEST_SceneManager::TEST_CreateScene()
//{
//  std::shared_ptr<Scene> pTestScene = sceneManager.CreateScene("testScene1");
//  if (pTestScene)
//  {
//    return true;
//  }
//  return false;
//}
//
//bool TEST_SceneManager::TEST_GetScene()
//{
//  std::shared_ptr<Scene> pTestScene = sceneManager.GetScene("testScene1");
//
//  /*if (pTestScene.GetSceneName() == "testScene1")
//  {
//    return true;
//  }*/
//
//  return false;
//}
