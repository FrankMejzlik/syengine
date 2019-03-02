#pragma once

#include "Script.h"
#include "Scene.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "FirstPersonCameraController.h"

namespace SYE
{

class _SceneBuilder 
{
public:
  void SetupScene(Scene* pScene)
  {
    // Create Camera 
    {
      Entity* pCameraEntity = pScene->CreateCamera(
        Vector3f(0.2f, -15.0f, 10.0f),
        Vector3f(0.0f, 0.0f, 0.0f),
        (dfloat)-M_PI_2, 0.57f, // Look at pinball maching under correct angle
        true
      );
      // Add ScriptHanlder Component
      ScriptHandler* pScriptHander = pCameraEntity->AddComponent<ScriptHandler>();
      // Attach specific script to it
      pScriptHander->AddScript<FirstPersonCameraController>();
    }

    // Construct pinball area
    {
      MeshRenderer* pMeshRenderer;

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
        pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 64.0f);
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
    }

    // Create ball
    {
      Entity* pSphere;
      MeshRenderer* pMeshRenderer;

      pSphere = pScene->CreateSphere(
        Vector3f(4.0f, 0.0f, -9.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
        0.5f, 20ULL, 20ULL,
        false, 0.1f
      );
      pMeshRenderer = pSphere->GetMeshRendererPtr();
      if (pMeshRenderer != nullptr)
      {
        pMeshRenderer->ClearMaterials();
        pMeshRenderer->AddMaterial(Vector3f(255.0f, 255.0f, 0.0f), 1.0f, 512.0f);
      }
    }


    // Create DirectionalLight
    pScene->CreateDirectionalLight(
      Vector3f(0.0f, 0.0f, 0.0f),          // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),          // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),          // scale vector

      Vector3f(1.0f, 1.0f, 1.0f),          // Colour vector
      Vector3f(0.7f, 0.5f, 0.1f),          // Intensities
      Vector3u(2048, 2048, 0),              // Shadow dimensions
      Vector3f(7.0f, -5.0f, -3.0f)
    );

    // Create PointLight
    pScene->CreatePointLight(
      Vector3f(0.0f, 0.0f, -5.0f),       // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

      Vector3f(1.0f, 0.0f, 0.0f),        // Colour vector
      Vector3f(0.0f, 1.0f, 0.0f),        // Intensities
      Vector3u(2048, 2048, 0),            // Shadow dimensions
      0.01f, 100.0f,                     // Plane dimensions
      Vector3f(0.02f, 0.06f, 0.03f)      // Coefficients
    );

    // Create SpotLight
    pScene->CreateSpotLight(
      Vector3f(-8.0f, 11.0f, -4.0f),       // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

      Vector3f(1.0f, 0.0f, 1.0f),        // Colour vector
      Vector3f(0.0f, 1.0f, 0.5f),        // Intensities
      Vector3u(2048, 2048, 0),  // Shadow dimensions
      0.01f, 100.0f,           // Plane dimensions
      Vector3f(0.02f, 0.003f, 0.008f),      // Coefficients

      Vector3f(1.0f, -1.0f, -1.0f),      // Light direction
      35.0f                                // Cone angle (degrees)
    );



  #if 1 // Draw coordinate gizmos

    Entity* pEntity;
    MeshRenderer* pMR;

    // X - red
    pEntity = pScene->CreateBlock(
      Vector3f(1.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, (dfloat)M_PI_2), Vector3f(1.0f, 1.0f, 1.0f),
      0.2f, 2.0f, 0.2f,
      true
    );
    pMR = pEntity->GetMeshRendererPtr();
    if (pMR != nullptr)
    {
      pMR->ClearMaterials();
      pMR->AddMaterial(Vector3f(1.f, 0.0f, 0.0f), 1.0f, 1024.0f);
    }

    // Y - green
    pEntity = pScene->CreateBlock(
      Vector3f(0.0f, 1.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      0.2f, 2.0f, 0.2f,
      true
    );
    pMR = pEntity->GetMeshRendererPtr();
    if (pMR != nullptr)
    {
      pMR->ClearMaterials();
      pMR->AddMaterial(Vector3f(0.f, 1.0f, 0.0f), 1.0f, 1024.0f);
    }


    // Z - blue
    pEntity = pScene->CreateBlock(
      Vector3f(0.0f, 0.0f, 1.0f), Vector3f((dfloat)M_PI_2, 0.0f, 0.0f * DEG_TO_RAD), Vector3f(1.0f, 1.0f, 1.0f),
      0.2f, 2.0f, 0.2f,
      true
    );
    pMR = pEntity->GetMeshRendererPtr();
    if (pMR != nullptr)
    {
      pMR->ClearMaterials();
      pMR->AddMaterial(Vector3f(0.f, 0.0f, 1.0f), 1.0f, 1024.0f);
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

    Entity* pSphere;
    MeshRenderer* pMeshRenderer;

    pSphere = pScene->CreateSphere(
      Vector3f(-10.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pSphere->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(1.f, 1.0f, 0.0f), 1.0f, 1024.0f);
    }

    pSphere = pScene->CreateSphere(
      Vector3f(10.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pSphere->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.0f, 1.0f, 0.0f), 0.1f, 32.0f);
    }

    pSphere = pScene->CreateSphere(
      Vector3f(-10.0f, 0.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pSphere->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(0.0f, 0.0f, 1.0f), 0.1f, 32.0f);
    }

    pSphere = pScene->CreateSphere(
      Vector3f(10.0f, 0.0f, 10.0f), Vector3f(1.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      1.0f, 20ULL, 20ULL,
      false, 0.1f
    );
    pMeshRenderer = pSphere->GetMeshRendererPtr();
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