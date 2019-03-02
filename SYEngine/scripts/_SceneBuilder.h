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
    Entity* pCameraEntity = pScene->CreateCamera(
      Vector3f(10.0f, 10.0f, 10.0f),
      Vector3f(0.0f, 1.0f, 0.0f),
      4.0f, -0.8f,
      true
    );
    // Add ScriptHanlder Component
    ScriptHandler* pScriptHander = pCameraEntity->AddComponent<ScriptHandler>();
    // Attach specific script to it
    pScriptHander->AddScript<FirstPersonCameraController>();

  #if 1 // 4 static floor block planes

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


    // Create DirectionalLight
    pScene->CreateDirectionalLight(
      Vector3f(0.0f, 0.0f, 0.0f),          // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),          // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),          // scale vector

      Vector3f(1.0f, 1.0f, 1.0f),          // Colour vector
      Vector3f(0.1f, 0.5f, 0.1f),          // Intensities
      Vector3u(2048, 2048, 0),              // Shadow dimensions
      Vector3f(7.0f, -5.0f, 3.0f)
    );

    // Create PointLight
    pScene->CreatePointLight(
      Vector3f(5.0f, -5.0f, 5.0f),       // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

      Vector3f(1.0f, 0.0f, 0.0f),        // Colour vector
      Vector3f(0.0f, 1.0f, 0.0f),        // Intensities
      Vector3u(2048, 2048, 0),            // Shadow dimensions
      0.01f, 100.0f,                     // Plane dimensions
      Vector3f(0.01f, 0.06f, 0.02f)      // Coefficients
    );

    // Create SpotLight
    pScene->CreateSpotLight(
      Vector3f(-6.0f, -4.0f, -6.0f),       // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // scale vector

      Vector3f(0.0f, 0.0f, 1.0f),        // Colour vector
      Vector3f(0.0f, 1.0f, 0.0f),        // Intensities
      Vector3u(2048, 2048, 0),  // Shadow dimensions
      0.01f, 100.0f,           // Plane dimensions
      Vector3f(0.01f, 0.06f, 0.02f),      // Coefficients

      Vector3f(1.0f, -1.0f, 1.0f),      // Light direction
      20.0f                                // Cone angle (degrees)
    );

  }

};

}