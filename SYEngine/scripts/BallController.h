#pragma once

#include "common.h"
#include "InputManager.h"
#include "Script.h"
#include "ScriptHandler.h"
#include "PhysicsBody.h"
#include "PhysicsEntity.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "MotionState.h"
#include "PointLight.h"

namespace SYE 
{

class BallController :
  public Script
{
  // Methods.
public:
  BallController() = delete;
  BallController(Entity* pOwnerEntity, Component* pOwnerComponent) :
    Script(pOwnerEntity, pOwnerComponent, UNDEFINED, Component::eType::SCRIPT),
    _launchStrength(0.21f),
    _launchEnergyGrowth(1.0f),
    _closingRoom(false),
    _isOutOfStartingRoom(false),
    _pPhysicsEntity(nullptr),
    _closeDelay(1.0f),
    pBackBase(nullptr),
    _currDiffuseLightIntensity(0.001f),
    _currAmbientLightIntensity(0.0f),
    _diffuseLightGworth(0.01f),
    _ambientLightIntensity(0.0001f),
    _isDiffuseIntensityFull(false),
    _score(0ULL)
  {}
  virtual ~BallController() noexcept {}


  /**
   * Initialize this script
   *
   * Called once when parent Entity is being initialized.
   */
  virtual void OnInitializeScene()
  {
    _pPhysicsEntity = GetRigidbodyPtr()->GetPhysicsEntity();
    _pPointLight = GetPointLightPtr();
  }

  /**
   * Do all things you need to do in each frame
   *
   * Called once per frame.
   */
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene)
  {
    _pScene = pScene;

    UNREFERENCED_PARAMETER(deltaTime);
    UNREFERENCED_PARAMETER(pScene);

    // If ball was fired
    if (_closingRoom)
    {
      // Subtract dt from remaining time
      _closeDelay -= deltaTime;

      if (_closeDelay < 0.0f)
      {
        CloseStartingRoom();
        _closingRoom = false;
      }
    }

    ProcessKeyControl(deltaTime, pScene);
  }

  void TickScore()
  {
    ++_score;

    DLog(eLogType::Info, "Score: %d", _score);
  }

  void CloseStartingRoom()
  {
    // Spawn blocking door to starting chamber
    pBackBase = _pScene->CreatePrism(
      Vector3f(5.0f, -6.0f, -8.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
      Vector3f(0.0f, 0.0f, 0.0f),
      Vector3f(0.0f, 0.0f, -1.0f), Vector3f(2.0f, 2.0f, -1.0f), Vector3f(2.0f, 2.5f, -1.0f), Vector3f(0.0f, 0.5f, -1.0f),
      Vector3f(0.0f, 0.0f, -0.0f), Vector3f(2.0f, 2.0f, 0.0f), Vector3f(2.0f, 2.5f, -0.0f), Vector3f(0.0f, 0.5f, 0.0f),
      true, // Is static
      0.0f  // No mass
    );
    auto pMeshRenderer = pBackBase->GetMeshRendererPtr();
    if (pMeshRenderer != nullptr)
    {
      pMeshRenderer->ClearMaterials();
      pMeshRenderer->AddMaterial(Vector3f(127.0f, 140.0f, 129.0f), 1.0f, 1024.0f);
    }
  }

  void ProcessKeyControl(dfloat deltaTime, Scene* pScene)
  {
    // If starting and laucnching
    if (!_isOutOfStartingRoom)
    {
      // Holding space increases launch strength
      if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_B))
      {
        _launchStrength = std::clamp(_launchStrength + _launchStrength * deltaTime * _launchEnergyGrowth, 0.0f, 1.0f);
      }

      // If space released
      if (pScene->GetInputManagerPtr()->IsOnKeyboardKeyUp(INPUT_KEY_B))
      {
        _pPhysicsEntity->SetLinearVelocity(Vector3f(0.0f, 350.0f, 0.0f) * _launchStrength);

        _closingRoom = true;
        _isOutOfStartingRoom = true;
      }

    }


    // If restert requested
    if (pScene->GetInputManagerPtr()->IsOnKeyboardKeyUp(INPUT_KEY_R))
    {
      btTransform trans;
      trans.setIdentity();
      trans.setOrigin(Vector3f(6.0f, -8.0f, -9.0f));
      _pPhysicsEntity->GetMotionState()->setWorldTransform(trans);
      _pPhysicsEntity->GetCollisionObjectPtr()->setWorldTransform(trans);

      // Reset forces
      static_cast<btRigidBody*>(_pPhysicsEntity->GetCollisionObjectPtr())->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));

      _closeDelay = 1.0f;

      _closingRoom = false;
      _isOutOfStartingRoom = false;

      if (pBackBase)
      {
        pScene->RemoveEntity(pBackBase);
      }
    }

  }

private:
  Entity* pBackBase;
  Scene* _pScene;

  size_t _score;

  bool _isOutOfStartingRoom;
  bool _closingRoom;
  dfloat _closeDelay;
  dfloat _launchStrength;
  dfloat _launchEnergyGrowth;

  dfloat _currDiffuseLightIntensity;
  dfloat _currAmbientLightIntensity;
  bool _isDiffuseIntensityFull;
  dfloat _diffuseLightGworth;
  dfloat _ambientLightIntensity;

  PhysicsEntity* _pPhysicsEntity;
  PointLight* _pPointLight;
};

};
  