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
    // Create lights
    ConstructLighting(pScene);

    // Create playground machine
    ConstructPinballMachine(pScene);

    // Create hitters
    ConstructHitters(pScene);

    // Create player paddles
    CreatePaddles(pScene);

    // Create ball
    CreateBalls(pScene);
    
    // Create Scene 
    AddCameras(pScene);

  }


private:
  /** 
   * Creates player balls present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void CreateBalls(Scene* pScene)
  {
    // Local variables used for building Scene
    Entity* pEntity;
    ScriptHandler* pScriptHander;
    MeshRenderer* pMeshRenderer;
    Rigidbody* pRigidbody;

    /*
     * Create Sphere entity
     * 
     * This will be our play ball.
     *
     * ATTACHED COMPONENTS:
     *  Transform
     *  MeshRenderer
     *  Rigidbody
     */
    pEntity = pScene->AddSphere(
      Vector3f(6.0f, -8.0f, -9.0f), // Position 
      Vector3f(0.0f, 0.0f, 0.0f),   // Rotation
      Vector3f(1.0f, 1.0f, 1.0f),   // Scale
      0.5f, // Radius
      20ULL, // Stack count
      20ULL, // Slice count
      false, // Is not static
      0.1f   // Mass
    );

    // We get MeshRenderer that is implicitly attached to this Entity
    pMeshRenderer = pEntity->GetMeshRendererPtr();

    // We check if there is any just to be sure
    if (pMeshRenderer != nullptr)
    {
      // Delete all existing materials (if any)
      pMeshRenderer->ClearMaterials();
      // Set new Material to this RGB coloured with provided specular and shininess intensities
      pMeshRenderer->AddMaterial(Vector3f(66.0f, 0.0f, 0.0f), 1.0f, 512.0f);
    }

    // We get Rigidbody that is implicitly attached to this Entity
    pRigidbody = pEntity->GetRigidbodyPtr();

    // We check if there is any just to be sure
    if (pRigidbody != nullptr)
    {
      /* Set tag to this Rigibody ball

      This is used in collision callbacks in your scripts to 
      detect collision with other correct Rigidbody */
      pRigidbody->SetTag(1ULL);
    }

    /*
     * Custom ball Script behaviour
     */
    { 
    // Add ScriptHanlder Component that we will attach our custom Script to that we will attach our custom Script to
      pScriptHander = pEntity->AddComponent<ScriptHandler>();

      // Add ScriptHanlder Component that we will attach our custom Script to, this is our Custom behaviour script
      pScriptHander->AddScript<BallController>();
    }

    /*
     * Point light on ball 
     */
    {
      // Add PointLight Component, this light will be attached to this ball
      PointLight* pLight = pEntity->AddComponent<PointLight>();

      // Set light colour
      pLight->SetColour(glm::vec3(255.0f, 30.0f, 30.0f));

      /* Set initial light intensities

      We're going to increase them as score goes up in BallController script. */
      pLight->SetInensities(glm::vec3(0.00, 0.0001f, 0.0f));

      /* Set dimensions of shadow maps

      E.g. 512x512 should be enough, do not go over 1024 - fully dynamic ligts are performance killer.*/
      pLight->SetShadowDimensions(glm::vec3(DEFAULT_SHADOW_MAP_DIMENSIONS, DEFAULT_SHADOW_MAP_DIMENSIONS, 0), 0.01f, 100.0f);

      /* Set attenuation coefficients to describe how light will spread in space

      For more info: http://ogldev.atspace.co.uk/www/tutorial20/tutorial20.html */
      pLight->SetCoeficients(glm::vec3(0.2f, 0.6f, 0.8f));
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();

    // Save this Entity as ball Entity
    _pBallEntity = pEntity;
  }

  /** 
   * Creates all Cameras present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void AddCameras(Scene* pScene)
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
    // Set this camera as main for this Scene
    pScene->SetMainCamera(pEntity->GetCameraPtr());

    /*
     * First person camera script
     * 
     * Allows you to 
     */
    {
    // Add ScriptHanlder Component that we will attach our custom Script to
      pScriptHander = pEntity->AddComponent<ScriptHandler>();

      // Attach new Script to it
      ActionCameraController* pCamController = pScriptHander->AddScript<ActionCameraController>();

      // Set pointer to ball object to Script
      pCamController->SetBallPtr(_pBallEntity->GetRigidbodyPtr());
    }

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
      Vector3f(0.0f, 0.5f, 0.1f),          // Intensities
      Vector3u(1024 , 1024 , 0),             // Shadow dimensions
      Vector3f(3.0f, -3.0f, -3.0f)         // Light direction
    );

    // Create top left SpotLight
    pScene->AddSpotLight(
      Vector3f(-8.0f, 11.0f, -4.0f),     // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // Rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // Scale vector
      Vector3f(1.0f, 0.0f, 1.0f),        // Colour vector
      Vector3f(0.8f, 1.0f, 1.0f),        // Intensities
      Vector3u(DEFAULT_SHADOW_MAP_DIMENSIONS , DEFAULT_SHADOW_MAP_DIMENSIONS , 0),           // Shadow dimensions
      0.01f, 100.0f,                     // Near and far plane distances
      Vector3f(0.01f, 0.02f, 0.03f),     // Coefficients
      Vector3f(1.0f, -1.0f, -1.0f),      // Light direction
      35.0f                              // Cone angle (degrees)
    );
  }

  /**                                                                          
   * Creates pinball machine present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void ConstructPinballMachine(Scene* pScene)
  {
    // Local variables used for building Scene
    MeshRenderer* pMeshRenderer;
    Entity* pEntity;

    /*
      * Back base of playfield
      */
    {
      /*
        * Create Block entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddBlock(
        Vector3f(0.0f, 0.0f, -10.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        14.0f, 1.0f, 20.0f,
        true
      );
      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          0.0f, 1024.0f // Shininess coeficients
        );
      }
      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Invisible front "glass" barier
      */
    {
      /*
        * Create Block entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddBlock(
        Vector3f(0.0f, 0.0f, -8.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        14.0f, 1.0f, 20.0f,
        true
      );
      // Remove MeshRenderer so it is not visible in world
      pEntity->RemoveComponent(pEntity->GetMeshRendererPtr());

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Top border
      */
    {
      /*
        * Create Block entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddBlock(
        Vector3f(0.0f, 9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        14.0f, 0.5f, 1.0f,
        true
      );
      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 64.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }


    /*
      * Left border
      */
    {
      /*
        * Create Block entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddBlock(
        Vector3f(-6.75f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        0.5f, 19.0f, 1.0f,
        true
      );
      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 64.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Right border
      */
    {
      /*
        * Create Block entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddBlock(
        Vector3f(6.75f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        0.5f, 19.0f, 1.0f,
        true
      );

      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 64.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Left bottom border
      */
    {
      /*
        * Create Block entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddBlock(
        Vector3f(-4.5f, -9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        5.0f, 0.5f, 1.0f,
        true
      );

      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 64.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Right bottom border
      */
    {
      /*
        * Create Block entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddBlock(
        Vector3f(4.5f, -9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        5.0f, 0.5f, 1.0f,
        true
      );

      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 64.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Right top corner
      */
    {
      pEntity = pScene->AddPrism(
        Vector3f(6.5f, 9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(0.0f, 0.0f, 0.0f), 
        Vector3f(-1.0f, 0.0f, -1.0f), Vector3f(-3.0f, 0.0f, -1.0f), Vector3f(-0.0f, -3.0f, -1.0f), Vector3f(-0.0f, 0.0f, -1.0f),
        Vector3f(-1.0f, 0.0f, 0.0f), Vector3f(-3.0f, 0.0f, -0.0f),  Vector3f(-0.0f, -3.0f, 0.0f), Vector3f(-0.0f, 0.0f, -0.0f),
        
        true, // Is static
        0.0f  // No mass
      );
      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 64.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Left bottom barier
      */
    {
      /*
        * Create Prism entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddPrism(
        Vector3f(-7.0f, -9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(0.0f, 0.0f, -1.0f), Vector3f(5.0f, 0.0f, -1.0f), Vector3f(3.5f, 2.5f, -1.0f), Vector3f(0.0f, 4.0f, -1.0f),
        Vector3f(0.0f, 0.0f, -0.0f), Vector3f(5.0f, 0.0f, 0.0f), Vector3f(3.5f, 2.5f, -0.0f), Vector3f(0.0f, 4.0f, 0.0f),
        true, // Is static
        0.0f  // No mass
      );

      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 1024.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }

    /*
      * Right bottom barier
      */
    {
      /*
        * Create Prism entity
        *
        * ATTACHED COMPONENTS:
        *  Transform
        *  MeshRenderer
        *  Rigidbody
        */
      pEntity = pScene->AddPrism(
        Vector3f(7.0f, -9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(-5.0f, 0.0f, -1.0f), Vector3f(-2.0f, 0.0f, -1.0f), Vector3f(-2.0f, 4.0f, -1.0f), Vector3f(-3.5f, 2.5f, -1.0f),
        Vector3f(-5.0f, 0.0f, -0.0f), Vector3f(-2.0f, 0.0f, 0.0f), Vector3f(-2.0f, 4.0f, -0.0f), Vector3f(-3.5f, 2.5f, 0.0f),
        true, // Is static
        0.0f  // No mass
      );

      // We get MeshRenderer that is implicitly attached to this Entity
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Delete all existing materials (if any)
        pMeshRenderer->ClearMaterials();
        // Add new Material with colour and Shininess
        pMeshRenderer->AddMaterial(
          Vector3f(127.0f, 140.0f, 129.0f), // Colour RGB value
          1.0f, 1024.0f // Shininess coeficients
        );
      }

      // Save all edits done on this Entity
      pEntity->SaveEntity();
    }
  }

  /** 
   * Creates all hittes present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void ConstructHitters(Scene* pScene)
  {
    // Local variables used for building Scene
    MeshRenderer* pMeshRenderer;
    Entity* pEntity;
    Rigidbody* pRigidbody;


    // Central
    pEntity = pScene->AddSphere(
      Vector3f(0.0f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.5f, 2.5f, 2.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Delete all existing materials (if any)
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.0f, 146.0f, 0.0f), 1.0f, 32.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(6.0f);
      pRigidbody->SetTag(2ULL);
    }
    // Add PointLight Component
    PointLight* pLight = pEntity->AddComponent<PointLight>();
    pLight->SetColour(glm::vec3(0.0f, 250.0f, 0.0f));
    pLight->SetInensities(glm::vec3(0.00, 0.05f, 0.0f));
    pLight->SetShadowDimensions(glm::vec3(512, 512, 0), 0.01f, 100.0f);
    pLight->SetCoeficients(glm::vec3(0.8f, 0.6f, 0.8f));
    pEntity->SaveEntity();


    // Devil 1
    pEntity = pScene->AddSphere(
      Vector3f(3.0f, 5.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Delete all existing materials (if any)
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(4.0f);
      pRigidbody->SetTag(2ULL);
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();


    // Devil 2
    pEntity = pScene->AddSphere(
      Vector3f(-3.0f, 5.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Delete all existing materials (if any)
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(4.0f);
      pRigidbody->SetTag(2ULL);
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();

    // Devil 3
    pEntity = pScene->AddSphere(
      Vector3f(-4.0f, -3.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Delete all existing materials (if any)
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(4.0f);
      pRigidbody->SetTag(2ULL);
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();

    // Devil 4
    pEntity = pScene->AddSphere(
      Vector3f(4.0f, -3.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(4.0f);
      pRigidbody->SetTag(2ULL);
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();

    // Medium 3
    pEntity = pScene->AddSphere(
      Vector3f(2.0f, 3.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.2f, 1.2f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(139.0f, 191.0f, 193.0f), 1.0f, 64.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(2.0f);
      pRigidbody->SetTag(2ULL);
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();

    // Medium 4
    pEntity = pScene->AddSphere(
      Vector3f(-2.0f, 3.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.2f, 1.2f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(139.0f, 191.0f, 193.0f), 1.0f, 64.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(2.0f);
      pRigidbody->SetTag(2ULL);
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();


    // Low 1
    pEntity = pScene->AddSphere(
      Vector3f(0.0f, -4.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.2f, 1.2f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.0f, 191.0f, 255.0f), 1.0f, 64.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetRestitution(1.5f);
      pRigidbody->SetTag(2ULL);
    }

    // Save all edits done on this Entity
    pEntity->SaveEntity();
  }

  /** 
   * Creates paddles that player will control
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */

  void CreatePaddles(Scene* pScene)
  {
    // Local variables used for building Scene
    Entity* pEntity;
    Transform* pTransform;
    ScriptHandler* pScriptHander;
    Rigidbody* pRigidbody;

    // Right paddle
    pEntity = pScene->AddPrism(
      Vector3f(1.5f, -8.0f, -8.51f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      Vector3f(0.0f, 0.0f, 0.0f),
      Vector3f(-1.0f, -0.1f, -1.0f), Vector3f(1.5f, -0.2f, -1.0f), Vector3f(1.5f, 0.2f, -1.0f), Vector3f(-1.0f, 0.1f, -1.0f),
      Vector3f(-1.0f, -0.1f, -0.0f), Vector3f(1.5f, -0.2f, 0.0f), Vector3f(1.5f, 0.2f, -0.0f), Vector3f(-1.0f, 0.1f, 0.0f),
      true, // Is static
      0.0f  // No mass
    );
    // Get Transfrom
    pTransform = pEntity->GetTransformPtr();
    if (pTransform != nullptr)
    {
      // Change origin point
      pTransform->SetOrigin(Vector3f(-1.5f, 0.0f, 0.0f));
    }
    // Add ScriptHanlder Component that we will attach our custom Script to
    pScriptHander = pEntity->AddComponent<ScriptHandler>();
    // Add ScriptHanlder Component that we will attach our custom Script to
    pScriptHander->AddScript<RightPaddleController>();

    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetIsKinematic(true);
    }

    // Left paddle
    pEntity = pScene->AddPrism(
      Vector3f(-4.5f, -8.0f, -8.51f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      Vector3f(0.0f, 0.0f, 0.0f),
      Vector3f(1.5f, 0.2f, -1.0f), Vector3f(-1.0f, 0.1f, -1.0f), Vector3f(-1.0f, -0.1f, -1.0f), Vector3f(1.5f, -0.2f, -1.0f),
      Vector3f(1.5f, 0.2f, -0.0f), Vector3f(-1.0f, 0.1f, 0.0f), Vector3f(-1.0f, -0.1f, -0.0f), Vector3f(1.5f, -0.2f, 0.0f),
      true, // Is static
      0.0f  // No mass
    );
    // Get Transfrom
    pTransform = pEntity->GetTransformPtr();
    if (pTransform != nullptr)
    {
      // Change origin point
      pTransform->SetOrigin(Vector3f(-1.5f, 0.0f, 0.0f));
    }
    // Add ScriptHanlder Component that we will attach our custom Script to
    pScriptHander = pEntity->AddComponent<ScriptHandler>();
    // Add ScriptHanlder Component that we will attach our custom Script to
    pScriptHander->AddScript<LeftPaddleController>();

    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetIsKinematic(true);
    }
  }

  protected:
    /** Pointer to Entity that represents ball */
    Entity* _pBallEntity;

};


}