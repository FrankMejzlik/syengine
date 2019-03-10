#pragma once

/*!
 * General input handler
 */


#include "common.h"
#include "MathLibrary.h"
#include "Script.h"

#include "RenderingManager.h"
#include "EngineContext.h"

namespace SYE 
{

class Entity;
class Component;

class GeneralInputHandler :
  public Script
{
  // Methods
public:
  GeneralInputHandler() = delete;
  GeneralInputHandler(Entity* pOwnerEntity, Component* pOwnerComponent) :
    Script(pOwnerEntity, pOwnerComponent, UNDEFINED, Component::eType::SCRIPT)
  {}
  virtual ~GeneralInputHandler() noexcept {}


  /**
   * Initialize this script
   *
   * Called once when parent Entity is being initialized.
   */
  virtual void OnInitializeScene()
  {
    
  }

  /**
   * Do all things you need to do in each frame
   *
   * Called once per frame.
   */
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene)
  {
    ProcessKeyboardInput(deltaTime, pScene);
    ProcessMouseKeyInput(deltaTime, pScene);
  }

  void ProcessKeyboardInput(dfloat deltaTime, Scene* pScene)
  {
    UNREFERENCED_PARAMETER(deltaTime);
    UNREFERENCED_PARAMETER(pScene);


    InputManager* pInputManager = pScene->GetInputManagerPtr();

    // If ESC pressed
    if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_ESCAPE))
    {
      // Tell engine to end
      GetEngineContextPtr()->SetShouldRun(false);
    }

    // If F1 pressed
    if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F1))
    {
      // Toggle physics debug draw of wireframe collision geometry
      GetRenderingManagerPtr()->TogglePhysicsDrawWireframe();
    }
    // If F2 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F2))
    {
      // Toggle debug draw of physics AABBs
      GetRenderingManagerPtr()->TogglePhysicsDrawAABBs();
    }
    // If F3 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F3))
    {

    }
    // If F4 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F4))
    {

    }
    // If F5 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F5))
    {

    }
    // If F6 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F6))
    {

    }
    // If F7 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F7))
    {

    }
    // If F8 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F8))
    {

    }
    // If F9 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F9))
    {

    }
    // If F10 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F10))
    {

    }
    // If F11 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F11))
    {

    }
    // If F12 pressed
    else if (pInputManager->IsOnKeyboardKeyDown(INPUT_KEY_F12))
    {

    }


    if (pScene->GetInputManagerPtr()->IsOnKeyboardKeyDown(INPUT_KEY_K))
    {
      
    }

    if (pScene->GetInputManagerPtr()->IsOnKeyboardKeyDown(INPUT_KEY_L))
    {
      
    }


    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_W))
    {
      
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_S))
    {
      
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_A))
    {
      
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_D))
    {
      
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_SPACE) && !pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_LEFT_SHIFT))
    {
      
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_SPACE) && pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_LEFT_SHIFT))
    {
      
    }

  }

  void ProcessMouseKeyInput(dfloat deltaTime, Scene* pScene)
  {
    UNREFERENCED_PARAMETER(deltaTime);
    UNREFERENCED_PARAMETER(pScene);


    if (pScene->GetInputManagerPtr()->IsMouseKeyDown(INPUT_MOUSE_BUTTON_RIGHT))
    {
      
    }
    else
    {
      
    }
  }


private:

};

};
  