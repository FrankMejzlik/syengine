#pragma once

/** 
* @file
* @breif Class @ref SYE::_SceneBuilder implementation
*/

#include "Script.h"
#include "Scene.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "PointLight.h"

#include "script_includes.h"

namespace SYE
{

/**
 * @brief   Class responsible for building initial Scene instance before launch
 */
class _SceneBuilder
{
public:
  /**
   * Builds initial scene.
   *
   * This is special script that is executed exactly once before game itself starts.
   *
   * @param   Scene*  Pointer to Scene instance we are building
   * @return  void
   */
  void SetupScene(Scene* pScene)
  {
    // Local variables used for building Scene
    MeshRenderer* pMeshRenderer;
    Entity* pEntity;
    Transform* pTransform;
    ScriptHandler* pScriptHander;
    Rigidbody* pRigidbody;

    // Create lights
    ConstructLighting(pScene);

    // Create playground machine
    ConstructPinballMachine(pScene);

    // Create player paddles
    CreatePaddles(pScene);
    
    CreateCameras(pScene);

    CreateBalls(pScene);

  }


private:
  /** 
   * Creates player balls present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void CreateCameras(Scene* pScene)
  {
    // Local variables used for building Scene
    Entity* pEntity;
    ScriptHandler* pScriptHander;
    MeshRenderer* pMeshRenderer;
    Rigidbody* pRigidbody;

    /*
     * Create Sphere entity
     *
     * ATTACHED COMPONENTS:
     *  Transform
     *  MeshRenderer
     *  Rigidbody
     */
    pEntity = pScene->CreateSphere(
      Vector3f(6.0f, -8.0f, -9.0f), // Position 
      Vector3f(0.0f, 0.0f, 0.0f),   // Rotation
      Vector3f(1.0f, 1.0f, 1.0f),   // Scale
      0.5f, // Radius
      20ULL, // Stack count
      20ULL, // Slice count
      false, // Is not static
      0.1f   // Mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(66.0f, 0.0f, 0.0f), 1.0f, 512.0f);
    }
    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetToContiniousCollision();
      // Set tag to ball to detect hitter collisions (1 + 2 -> hitter + ball) for score
      pRigidbody->SetTag(1ULL);
    }
    // Add ScriptHanlder Component
    pScriptHander = pEntity->AddComponent<ScriptHandler>();
    // Attach specific script to it
    pScriptHander->AddScript<BallController>();

    // Add DirectionalLight Component
    PointLight* pLight = pEntity->AddComponent<PointLight>();
    pLight->SetColour(glm::vec3(255.0f, 30.0f, 30.0f));
    pLight->SetInensities(glm::vec3(0.00, 0.0001f, 0.0f));
    pLight->SetShadowDimensions(glm::vec3(2048, 2048, 0), 0.01f, 100.0f);
    pLight->SetCoeficients(glm::vec3(0.02f, 0.06f, 0.08f));

    // Save all edits done on this Entity
    pEntity->SaveEntity();
  }

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

    // Add ScriptHanlder Component
    pScriptHander = pEntity->AddComponent<ScriptHandler>();

    // Attach new Script to it
    FirstPersonCameraController* pCamController = pScriptHander->AddScript<FirstPersonCameraController>();

    // Set pointer to ball object to Script
    pCamController->SetBallPtr(pEntity->GetRigidbodyPtr());

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
    pScene->CreateDirectionalLight(
      Vector3f(0.0f, 0.0f, 0.0f),          // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),          // Rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),          // Scale vector
      Vector3f(1.0f, 1.0f, 1.0f),          // Colour vector
      Vector3f(0.0f, 0.5f, 0.1f),          // Intensities
      Vector3u(2048, 2048, 0),             // Shadow dimensions
      Vector3f(7.0f, -5.0f, -3.0f)         // Light direction
    );

    // Create top left SpotLight
    pScene->CreateSpotLight(
      Vector3f(-8.0f, 11.0f, -4.0f),     // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // Rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // Scale vector
      Vector3f(1.0f, 0.0f, 1.0f),        // Colour vector
      Vector3f(0.8f, 1.0f, 1.0f),        // Intensities
      Vector3u(2048, 2048, 0),           // Shadow dimensions
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
    Transform* pTransform;
    Rigidbody* pRigidbody;


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
      pEntity = pScene->CreateBlock(
        Vector3f(0.0f, 0.0f, -10.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        14.0f, 1.0f, 20.0f,
        true
      );
      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreateBlock(
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
      pEntity = pScene->CreateBlock(
        Vector3f(0.0f, 9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        14.0f, 0.5f, 1.0f,
        true
      );
      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreateBlock(
        Vector3f(-6.75f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        0.5f, 19.0f, 1.0f,
        true
      );
      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreateBlock(
        Vector3f(6.75f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        0.5f, 19.0f, 1.0f,
        true
      );

      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreateBlock(
        Vector3f(-4.5f, -9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        5.0f, 0.5f, 1.0f,
        true
      );

      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreateBlock(
        Vector3f(4.5f, -9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        5.0f, 0.5f, 1.0f,
        true
      );

      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreatePrism(
        Vector3f(6.5f, 9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(-3.0f, 0.0f, -1.0f), Vector3f(-0.0f, -3.0f, -1.0f), Vector3f(-0.0f, 0.0f, -1.0f), Vector3f(-1.0f, 0.0f, -1.0f),
        Vector3f(-3.0f, 0.0f, -0.0f), Vector3f(-0.0f, -3.0f, 0.0f), Vector3f(-0.0f, 0.0f, -0.0f), Vector3f(-1.0f, 0.0f, 0.0f),
        true, // Is static
        0.0f  // No mass
      );
      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreatePrism(
        Vector3f(-7.0f, -9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(0.0f, 0.0f, -1.0f), Vector3f(5.0f, 0.0f, -1.0f), Vector3f(3.5f, 2.5f, -1.0f), Vector3f(0.0f, 4.0f, -1.0f),
        Vector3f(0.0f, 0.0f, -0.0f), Vector3f(5.0f, 0.0f, 0.0f), Vector3f(3.5f, 2.5f, -0.0f), Vector3f(0.0f, 4.0f, 0.0f),
        true, // Is static
        0.0f  // No mass
      );

      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
      pEntity = pScene->CreatePrism(
        Vector3f(7.0f, -9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(-5.0f, 0.0f, -1.0f), Vector3f(-2.0f, 0.0f, -1.0f), Vector3f(-2.0f, 4.0f, -1.0f), Vector3f(-3.5f, 2.5f, -1.0f),
        Vector3f(-5.0f, 0.0f, -0.0f), Vector3f(-2.0f, 0.0f, 0.0f), Vector3f(-2.0f, 4.0f, -0.0f), Vector3f(-3.5f, 2.5f, 0.0f),
        true, // Is static
        0.0f  // No mass
      );

      // Get MeshRenderer Component ptr
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        // Clear current materials
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
    Transform* pTransform;
    ScriptHandler* pScriptHander;
    Rigidbody* pRigidbody;


    // Central
    pEntity = pScene->CreateSphere(
      Vector3f(0.0f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.5f, 2.5f, 2.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Clear current materials
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
    pLight->SetShadowDimensions(glm::vec3(2048, 2048, 0), 0.01f, 100.0f);
    pLight->SetCoeficients(glm::vec3(0.8f, 0.6f, 0.8f));
    pEntity->SaveEntity();


    // Devil 1
    pEntity = pScene->CreateSphere(
      Vector3f(3.0f, 5.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Clear current materials
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
    pEntity = pScene->CreateSphere(
      Vector3f(-3.0f, 5.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Clear current materials
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
    pEntity = pScene->CreateSphere(
      Vector3f(-4.0f, -3.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
      0.5f, 20, 20,
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      // Clear current materials
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
    pEntity = pScene->CreateSphere(
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
    pEntity = pScene->CreateSphere(
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
    pEntity = pScene->CreateSphere(
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
    pEntity = pScene->CreateSphere(
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
    MeshRenderer* pMeshRenderer;
    Entity* pEntity;
    Transform* pTransform;
    ScriptHandler* pScriptHander;
    Rigidbody* pRigidbody;

    // Right paddle
    pEntity = pScene->CreatePrism(
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
    // Add ScriptHanlder Component
    pScriptHander = pEntity->AddComponent<ScriptHandler>();
    // Attach specific script to it
    pScriptHander->AddScript<RightPaddleController>();

    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetIsKinematic(true);
    }

    // Left paddle
    pEntity = pScene->CreatePrism(
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
    // Add ScriptHanlder Component
    pScriptHander = pEntity->AddComponent<ScriptHandler>();
    // Attach specific script to it
    pScriptHander->AddScript<LeftPaddleController>();

    pRigidbody = pEntity->GetRigidbodyPtr();
    if (pRigidbody != nullptr)
    {
      pRigidbody->SetIsKinematic(true);
    }
  }

};


}