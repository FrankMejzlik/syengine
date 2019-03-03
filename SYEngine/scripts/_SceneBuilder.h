#pragma once

#include "Script.h"
#include "Scene.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "PointLight.h"

#include "script_includes.h"

namespace SYE
{

class _SceneBuilder 
{
public:
  void SetupScene(Scene* pScene)
  {

    MeshRenderer* pMeshRenderer; pMeshRenderer;
    Entity* pEntity; pEntity;
    Transform* pTransform;
    ScriptHandler* pScriptHander;
    Rigidbody* rb;

    // Create Camera 
    {
      Entity* pCameraEntity = pScene->CreateCamera(
        Vector3f(0.2f, -15.0f, 10.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        (dfloat)-M_PI_2, 0.57f, // Look at pinball maching under correct angle
        true
      );
      // Add ScriptHanlder Component
      pScriptHander = pCameraEntity->AddComponent<ScriptHandler>();
      // Attach specific script to it
      pScriptHander->AddScript<FirstPersonCameraController>();
    }

  #if 1
    // Construct pinball area


      // Back base of playfield
    Entity* pBackBase = pScene->CreateBlock(
      Vector3f(0.0f, 0.0f, -10.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      14.0f, 1.0f, 20.0f,
      true
    );
    // Change colour
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 0.0f, 1024.0f);
    }
    
    // Create front invisible wall to prevent ball from falling out
    Entity* pInvisibleBlock = pScene->CreateBlock(
      Vector3f(0.0f, 0.0f, -8.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      14.0f, 1.0f, 20.0f,
      true
    );
    // Remove MeshRenderer to serve as invisible wall
    pInvisibleBlock->RemoveComponent(pInvisibleBlock->GetMeshRendererPtr());



    // Top border
    pBackBase = pScene->CreateBlock(
      Vector3f(0.0f, 9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      14.0f, 0.5f, 1.0f,
      true
    );
    // Change colour
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 64.0f);
    }

    // Left border
    pBackBase = pScene->CreateBlock(
      Vector3f(-6.75f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      0.5f, 19.0f, 1.0f,
      true
    );
    // Change colour
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 64.0f);
    }

    // Right border
    pBackBase = pScene->CreateBlock(
      Vector3f(6.75f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      0.5f, 19.0f, 1.0f,
      true
    );
    // Change colour
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 64.0f);
    }

    // Left bottom
    pBackBase = pScene->CreateBlock(
      Vector3f(-4.5f, -9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      5.0f, 0.5f, 1.0f,
      true
    );
    // Change colour
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 64.0f);
    }

    // Right bottom
    pBackBase = pScene->CreateBlock(
      Vector3f(4.5f, -9.75f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      5.0f, 0.5f, 1.0f,
      true
    );
    // Change colour
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 64.0f);
    }


    // Right top corner
    pBackBase = pScene->CreatePrism(
      Vector3f(6.5f, 9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      Vector3f(0.0f, 0.0f, 0.0f),
      Vector3f(-3.0f, 0.0f, -1.0f), Vector3f(-0.0f, -3.0f, -1.0f), Vector3f(-0.0f, 0.0f, -1.0f), Vector3f(-1.0f, 0.0f, -1.0f),
      Vector3f(-3.0f, 0.0f, -0.0f), Vector3f(-0.0f, -3.0f, 0.0f), Vector3f(-0.0f, 0.0f, -0.0f), Vector3f(-1.0f, 0.0f, 0.0f),
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 64.0f);
    }


    // Left bottom barier 
    pBackBase = pScene->CreatePrism(
      Vector3f(-7.0f, -9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      Vector3f(0.0f, 0.0f, 0.0f),
      Vector3f(0.0f, 0.0f, -1.0f), Vector3f(5.0f, 0.0f, -1.0f), Vector3f(3.5f, 2.5f, -1.0f), Vector3f(0.0f, 4.0f, -1.0f),
      Vector3f(0.0f, 0.0f, -0.0f), Vector3f(5.0f, 0.0f, 0.0f), Vector3f(3.5f, 2.5f, -0.0f), Vector3f(0.0f, 4.0f, 0.0f),
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 1024.0f);
    }

    // Right bottom barier 
    pBackBase = pScene->CreatePrism(
      Vector3f(7.0f, -9.5f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      Vector3f(0.0f, 0.0f, 0.0f),
      Vector3f(-5.0f, 0.0f, -1.0f), Vector3f(-2.0f, 0.0f, -1.0f), Vector3f(-2.0f, 4.0f, -1.0f), Vector3f(-3.5f, 2.5f, -1.0f),
      Vector3f(-5.0f, 0.0f, -0.0f), Vector3f(-2.0f, 0.0f, 0.0f), Vector3f(-2.0f, 4.0f, -0.0f), Vector3f(-3.5f, 2.5f, 0.0f),
      true, // Is static
      0.0f  // No mass
    );
    pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 1024.0f);
    }


    /**
     * Mid blockers
     */
     // #1
    //pBackBase = pScene->CreateBlock(
    //  Vector3f(2.0f, -3.75f, -9.0f), Vector3f(0.0f, 0.0f, (dfloat)M_PI_4 * 1.5f), Vector3f(1.0f, 1.0f, 1.0f),
    //  3.0f, 0.2f, 1.0f,
    //  true
    //);
    //// Change colour
    //pMeshRenderer = pBackBase->GetMeshRendererPtr();
    //if (pMeshRenderer != nullptr)
    //{
    //  pMeshRenderer->ClearMaterials();
    //  pMeshRenderer->AddMaterial(Vector3f(027.0f, 240.0f, 229.0f), 1.0f, 64.0f);
    //}

    //// #2
    //pBackBase = pScene->CreateBlock(
    //  Vector3f(-2.0f, -3.75f, -9.0f), Vector3f(0.0f, 0.0f, (dfloat)M_PI_4 * -1.5f), Vector3f(1.0f, 1.0f, 1.0f),
    //  3.0f, 0.2f, 1.0f,
    //  true
    //);
    //// Change colour
    //pMeshRenderer = pBackBase->GetMeshRendererPtr();
    //if (pMeshRenderer != nullptr)
    //{
    //  pMeshRenderer->ClearMaterials();
    //  pMeshRenderer->AddMaterial(Vector3f(027.0f, 240.0f, 229.0f), 1.0f, 64.0f);
    //}


    /**
     * Hitters
     */
    {
      // Devil 1
      pBackBase = pScene->CreateSphere(
        Vector3f(2.0f, 5.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(3.0f);
        rb->SetTag(2ULL);
      }



      // Devil 2
      pBackBase = pScene->CreateSphere(
        Vector3f(-3.0f, 6.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(3.0f);
        rb->SetTag(2ULL);
      }

      // Devil 3
      pBackBase = pScene->CreateSphere(
        Vector3f(-3.0f, -2.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(3.0f);
        rb->SetTag(2ULL);
      }

      // Devil 4
      pBackBase = pScene->CreateSphere(
        Vector3f(3.0f, -2.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 2.0f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(24.0f, 146.0f, 150.0f), 1.0f, 1024.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(3.0f);
        rb->SetTag(2ULL);
      }


      // Medium 1
      pBackBase = pScene->CreateSphere(
        Vector3f(3.0f, -1.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.2f, 1.2f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(139.0f, 191.0f, 193.0f), 1.0f, 64.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(6.0f);
        rb->SetTag(2ULL);
      }


      // Medium 2
      pBackBase = pScene->CreateSphere(
        Vector3f(-3.0f, -1.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.2f, 1.2f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(139.0f, 191.0f, 193.0f), 1.0f, 64.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(6.0f);
        rb->SetTag(2ULL);
      }

      // Medium 3
      pBackBase = pScene->CreateSphere(
        Vector3f(1.0f, 3.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.2f, 1.2f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(139.0f, 191.0f, 193.0f), 1.0f, 64.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(6.0f);
        rb->SetTag(2ULL);
      }

      // Medium 4
      pBackBase = pScene->CreateSphere(
        Vector3f(-1.0f, 3.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.2f, 1.2f, 1.0f),
        0.5f, 20, 20,
        true, // Is static
        0.0f  // No mass
      );
      pMeshRenderer = pBackBase->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(139.0f, 191.0f, 193.0f), 1.0f, 64.0f);
      }
      rb = pBackBase->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetRestitution(6.0f);
        rb->SetTag(2ULL);
      }
    }


  #endif
    // Create paddles
    {
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

      rb = pEntity->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetIsKinematic(true);
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

      rb = pEntity->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetIsKinematic(true);
      }
    }

  #if 1

    // Create ball
    {
      pEntity = pScene->CreateSphere(
        Vector3f(6.0f, -8.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        0.5f, 20ULL, 20ULL,
        false, 0.1f
      );
      pMeshRenderer = pEntity->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(66.0f, 0.0f, 0.0f), 1.0f, 512.0f);
      }
      rb = pEntity->GetRigidbodyPtr();
      if (rb != nullptr)
      {
        rb->SetToContiniousCollision();
        // Set tag to ball to detect hitter collisions (1 + 2 -> hitter + ball) for score
        rb->SetTag(1ULL);
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

    }
 

  #endif

    // Create DirectionalLight
    pScene->CreateDirectionalLight(
      Vector3f(0.0f, 0.0f, 0.0f),          // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),          // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),          // scale vector

      Vector3f(1.0f, 1.0f, 1.0f),          // Colour vector
      Vector3f(0.0f, 0.5f, 0.1f),          // Intensities
      Vector3u(2048, 2048, 0),              // Shadow dimensions
      Vector3f(7.0f, -5.0f, -3.0f)
    );

    // Create PointLight
    //pScene->CreatePointLight(
    //  Vector3f(0.0f, 0.0f, -5.0f),       // Position vector
    //  Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
    //  Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

    //  Vector3f(1.0f, 0.0f, 0.0f),        // Colour vector
    //  Vector3f(0.0f, 1.0f, 0.0f),        // Intensities
    //  Vector3u(2048, 2048, 0),            // Shadow dimensions
    //  0.01f, 100.0f,                     // Plane dimensions
    //  Vector3f(0.02f, 0.06f, 0.03f)      // Coefficients
    //);

    // Create SpotLight
    pScene->CreateSpotLight(
      Vector3f(-8.0f, 11.0f, -4.0f),       // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

      Vector3f(1.0f, 0.0f, 1.0f),        // Colour vector
      Vector3f(0.8f, 1.0f, 1.0f),        // Intensities
      Vector3u(2048, 2048, 0),  // Shadow dimensions
      0.01f, 100.0f,           // Plane dimensions
      Vector3f(0.01f, 0.02f, 0.03f),      // Coefficients

      Vector3f(1.0f, -1.0f, -1.0f),      // Light direction
      35.0f                                // Cone angle (degrees)
    );

    // Create SpotLight
    pScene->CreateSpotLight(
      Vector3f(8.0f, 11.0f, -2.0f),       // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

      Vector3f(0.01f, 0.5f, 0.6f),        // Colour vector
      Vector3f(0.8f, 1.0f, 1.0f),        // Intensities
      Vector3u(2048, 2048, 0),  // Shadow dimensions
      0.01f, 100.0f,           // Plane dimensions
      Vector3f(0.01f, 0.02f, 0.03f),      // Coefficients

      Vector3f(-1.0f, -1.0f, -2.0f),      // Light direction
      35.0f                                // Cone angle (degrees)
    );



  #if 1 // Draw coordinate gizmos

    // X - red
    pEntity = pScene->CreateBlock(
      Vector3f(1.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, (dfloat)M_PI_2), Vector3f(1.0f, 1.0f, 1.0f),
      0.2f, 2.0f, 0.2f,
      true
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(1.f, 0.0f, 0.0f), 1.0f, 1024.0f);
    }

    // Y - green
    pEntity = pScene->CreateBlock(
      Vector3f(0.0f, 1.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      0.2f, 2.0f, 0.2f,
      true
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.f, 1.0f, 0.0f), 1.0f, 1024.0f);
    }


    // Z - blue
    pEntity = pScene->CreateBlock(
      Vector3f(0.0f, 0.0f, 1.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      0.2f, 2.0f, 0.2f,
      true
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.f, 0.0f, 1.0f), 1.0f, 1024.0f);
    }

  #endif


  #if 0 // 4 static floor block planes

    Entity* pBlock1 = pScene->CreateBlock(
      Vector3f(-10.0f, -20.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      9.0f, 1.0f, 9.0f,
      true
    );
    Rigidbody* pRb_block1 = pBlock1->GetRigidbodyPtr();
    if (pRb_block1 != nullptr)
    {
      pRb_block1->SetRestitution(0.5f);
    }

    pBlock1 = pScene->CreateBlock(
      Vector3f(10.0f, -20.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      9.0f, 1.0f, 9.0f,
      true
    );
    pRb_block1 = pBlock1->GetRigidbodyPtr();
    if (pRb_block1 != nullptr)
    {
      pRb_block1->SetRestitution(1.0f);
    }

    pBlock1 = pScene->CreateBlock(
      Vector3f(10.0f, -20.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      9.0f, 1.0f, 9.0f,
      true
    );
    pRb_block1 = pBlock1->GetRigidbodyPtr();
    if (pRb_block1 != nullptr)
    {
      pRb_block1->SetRestitution(1.5f);
    }

    pBlock1 = pScene->CreateBlock(
      Vector3f(-10.0f, -20.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      9.0f, 1.0f, 9.0f,
      true
    );
    pRb_block1 = pBlock1->GetRigidbodyPtr();
    if (pRb_block1 != nullptr)
    {
      pRb_block1->SetRestitution(2.0f);
    }

  #endif

  #if 1 // Small falling spheres

    pEntity = pScene->CreateSphere(
      Vector3f(-10.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(1.f, 1.0f, 0.0f), 1.0f, 1024.0f);
    }

    pEntity = pScene->CreateSphere(
      Vector3f(10.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.0f, 1.0f, 0.0f), 0.1f, 32.0f);
    }

    pEntity = pScene->CreateSphere(
      Vector3f(-10.0f, 0.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.0f, 0.0f, 1.0f), 0.1f, 32.0f);
    }

    pEntity = pScene->CreateSphere(
      Vector3f(10.0f, 0.0f, 10.0f), Vector3f(1.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pEntity->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearAll();
      pMeshRenderer->AddMaterial(Vector3f(0.0f, 0.0f, 0.0f), 0.1f, 32.0f);
    }

  #endif


  #if 0 // Small falling blocks

    pScene->CreateBlock(
      Vector3f(-10.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 1.0f, 1.0f,
      true, 1.0f
    );

    pScene->CreateBlock(
      Vector3f(10.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 1.0f, 1.0f,
      true, 1.0f
    );

    pScene->CreateBlock(
      Vector3f(10.0f, 0.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 1.0f, 1.0f,
      true, 1.0f
    );

    pScene->CreateBlock(
      Vector3f(-10.0f, 0.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 1.0f, 1.0f,
      true, 1.0f
    );

  #endif


  #if 0 // Lot of small falling blocks

    for (size_t i = 0; i < 10; ++i)
    {
      for (size_t j = 0; j < 10; ++j)
      {
        pScene->CreateBlock(
          Vector3f(-5.0f + (float)i, 10.0f, -10.0f + (float)j), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
          1.0f, 1.0f, 1.0f,
          true, 1.0f
        );
      }
    }

  #endif

  }

};

}