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

    // Create Lights
    ConstructLighting(pScene);

    /*
    * Create Block entity
    *
    * ATTACHED COMPONENTS:
    *  Transform
    *  MeshRenderer
    *  Rigidbody
    */
    Entity* pEntity = pScene->AddBlock(
      Vector3f(0.0f, 0.0f, -10.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      4.0f, 4.0f, 4.0f,
      true
    );
    // We get MeshRenderer that is implicitly attached to this Entity
    MeshRenderer* pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Delete all existing materials (if any)
      pMeshRenderer->ClearMaterials();
      // Add new Material with colour and Shininess
      pMeshRenderer->AddMaterial(
        Vector3f(127.0f, 255.0f, 0.0f), // Colour RGB value
        1.0f, 1024.0f // Shininess coeficients
      );
    }
    // Save all edits done on this Entity
    pEntity->SaveEntity();

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
    pEntity = pScene->AddCamera(
      Vector3f(0.2f, -15.0f, 10.0f),        // Position
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

    // Set main camera.
    pScene->SetMainCamera(pEntity->GetCameraPtr());

    // Save all edits done on this Entity
    pEntity->SaveEntity();
  }

  /** 
  * Creates Light present in initial Scene
  *
  *  @param  Scene*  Pointer to scene instance we're building
  *  @return void
  */
  void ConstructLighting(Scene* pScene)
  {
    // Create main DirectionalLight
    pScene->AddDirectionalLight(
      Vector3f(0.0f, 0.0f, 0.0f),          // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),          // Rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),          // Scale vector
      Vector3f(1.0f, 1.0f, 1.0f),          // Colour vector
      Vector3f(0.2f, 0.5f, 0.1f),          // Intensities
      Vector3u(1024 , 1024 , 0),             // Shadow dimensions
      Vector3f(3.0f, -3.0f, -3.0f)         // Light direction
    );

    // Create top left SpotLight
    pScene->AddSpotLight(
      Vector3f(-1.0f, 2.0f, -7.0f),     // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // Rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // Scale vector
      Vector3f(1.0f, 0.0f, 1.0f),        // Colour vector
      Vector3f(0.0f, 1.0f, 1.0f),        // Intensities
      Vector3u(DEFAULT_SHADOW_MAP_DIMENSIONS , DEFAULT_SHADOW_MAP_DIMENSIONS , 0),           // Shadow dimensions
      0.01f, 100.0f,                     // Near and far plane distances
      Vector3f(0.03f, 0.04f, 0.05f),     // Coefficients
      Vector3f(1.0f, -1.0f, -1.0f),      // Light direction
      35.0f                              // Cone angle (degrees)
    );
  }

};


}