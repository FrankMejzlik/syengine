#pragma once

/** 
* @file
* @breif Class @ref SYE::_SceneBuilder implementation
*/

#include "_SceneBuilderBase.h"
#include "Script.h"
#include "Scene.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "PointLight.h"

// Include all scripts you're gonna use
#include "game_script_includes.h"

namespace SYE
{

/**
 * Class responsible for building initial Scene instance before launch
 *
 * This is derrived class of abstract _SceneBuilderBase. This is concrete implementation
 * for concrete game that is being scripted.
 * 
 */
class _SceneBuilder:
  public _SceneBuilderBase
{
public:
  /**
   * Builds initial scene
   *
   * This is special script that is executed exactly once before game itself starts.
   *
   * @param   Scene*  Pointer to Scene instance we are building
   * @return  void
   */
  virtual void SetupScene(Scene* pScene) override
  {
    // Create Scene 
    CreateCameras(pScene);
  }


private:
  /** 
   * Creates all Cameras present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void CreateCameras(Scene* pScene)
  {
    // Local variables used for building Scene
    Entity* pEntity;
    ScriptHandler* pScriptHander;

    /*
     * Create Camera entity
     *
     * ATTACHED COMPONENTS:
     *  Transform
     *  Camera
     */
    pEntity = pScene->CreateCamera(
      Vector3f(0.2f, -15.0f, 10.0f),        // Position
      Vector3f(0.0f, 1.0f, 0.0f),           // Start up direction
      static_cast<dfloat>(-M_PI_2), 0.57f   // Start yaw and pitch (radians)
    );

    /*
     * General Input script handler
     * 
     * Provides global input on F1 - F12 keys.
     */
    {
      // Add ScriptHanlder Component that we will attach our custom Script to
      pScriptHander = pEntity->AddComponent<ScriptHandler>();

      // Attach new Script to it
      pScriptHander->AddScript<GeneralInputHandler>();
    }

    // Add ScriptHanlder Component
    pScriptHander = pEntity->AddComponent<ScriptHandler>();

    // Attach new Script to it
    FirstPersonCameraController* pCamController = pScriptHander->AddScript<FirstPersonCameraController>();
    pCamController;

    // Save all edits done on this Entity
    pEntity->SaveEntity();
  }

};


}