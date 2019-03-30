#pragma once


#include <algorithm>

#include "common.h"
#include "Script.h"
#include "MathLibrary.h"
#include "Transform.h"
#include "InputManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Window.h"
#include "ScriptHandler.h"

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#pragma warning(pop)

namespace SYE 
{
/**
 * Script for right paddle behaviour
 *
 * Main responsibilites:
 *    Move it on keypress to bounce ball.
 */
class LeftPaddleController :
  public Script
{
  // Methods.
public:
  LeftPaddleController() = delete;
  LeftPaddleController(Entity* pOwnerEntity, Component* pOwnerComponent):
    Script(pOwnerEntity, pOwnerComponent, UNDEFINED, Component::eType::SCRIPT),
    _paddleSpeed(20.0f),
    _currRotation(static_cast<dfloat>(M_PI - M_PI_4))
  {}


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
  virtual void OnProcessFrame([[maybe_unused]] dfloat deltaTime, [[maybe_unused]] Scene* pScene)
  {
    ProcessKeyControl(deltaTime, pScene);
  }

  void ProcessKeyControl(dfloat deltaTime, Scene* pScene)
  {
    
    dfloat deltaSpeed = _paddleSpeed * deltaTime;
    dfloat newAngle;

    // If left arrow held down
    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_LEFT))
    {
      newAngle = std::clamp(_currRotation + deltaSpeed, static_cast<dfloat>(-M_PI_4 + M_PI), static_cast<dfloat>(M_PI_4 + M_PI));

      // Update rotation
      _currRotation = newAngle;
    }
    // If not pressed, move back
    else
    {
      newAngle = std::clamp(_currRotation - deltaSpeed, static_cast<dfloat>(-M_PI_4 + M_PI), static_cast<dfloat>(M_PI_4 + M_PI));

      // Update rotation
      _currRotation = newAngle;
    }

    // Update position in Transform Component
    Vector3f rotation = GetTransformPtr()->GetRotation();
    rotation.SetZ(_currRotation);
    GetTransformPtr()->SetRotation(std::move(rotation));
  }
  
  // Attributes
private:
  dfloat _paddleSpeed;
  dfloat _currRotation;
};

};
  
