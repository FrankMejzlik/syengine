#pragma once


#include "common.h"
#include "Script.h"
#include "MathLibrary.h"
#include "Transform.h"
#include "InputManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Window.h"
#include "ScriptHandler.h"
#include "Camera.h"

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
class LookAtQuad :
  public Script
{
  // Methods.
public:
  LookAtQuad() = delete;
  LookAtQuad(Entity* pOwnerEntity, Component* pOwnerComponent):
    Script(pOwnerEntity, pOwnerComponent, UNDEFINED, Component::eType::SCRIPT),
    _pMainCameraPtr(nullptr)
  {}


  /**
   * Initialize this script
   *
   * Called once when parent Entity is being initialized.
   */
  virtual void OnInitializeScene()
  {
    _pMainCameraPtr = GetOwnerScenePtr()->GetMainCamera();
    _pTransformPtr = GetTransformPtr();
  }

  /**
   * Do all things you need to do in each frame
   *
   * Called once per frame.
   */
  virtual void OnProcessFrame([[maybe_unused]] dfloat deltaTime, [[maybe_unused]] Scene* pScene)
  {
    TransformCamera(deltaTime, pScene);
  }

  void TransformCamera([[maybe_unused]] dfloat deltaTime, [[maybe_unused]] Scene* pScene)
  {

    Vector3f camPosition = _pMainCameraPtr->GetTransformPtr()->GetPosition();
    Vector3f camDirectionn = _pMainCameraPtr->GetTransformPtr()->GetZDir();

    Vector3f quadPosition = camPosition + (camDirectionn * 5.0f);

    Vector3f dirToCam = -1 * camDirectionn;
    
    auto quatRot = glm::quatLookAt(dirToCam.GetData(), Vector3f(0.0f, 1.0f, 0.0f).GetData());

    glm::vec3 angles = glm::eulerAngles(quatRot);

    Vector3f finalRotationAngles(angles.y, angles.x, angles.z);

    _pTransformPtr->SetPosition(quadPosition);
    _pTransformPtr->SetRotation(angles);
  }

  // Attributes
private:
  Camera* _pMainCameraPtr;
  Transform* _pTransformPtr;
};

};
  