#pragma once

/**
 * First person Camera controller script
 *
 */

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#pragma warning(pop)

#include "common.h"
#include "Script.h"
#include "MathLibrary.h"
#include "Transform.h"
#include "InputManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Window.h"
#include "Rigidbody.h"
#include "ScriptHandler.h"

#pragma warning(push, 1)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

namespace SYE 
{

class FirstPersonCameraController :
  public Script
{
  // Structs
public:
  enum class eCameraMode
  {
    NORMAL, 
    EDITOR_CAMERA
  };

  // Methods.
public:
  FirstPersonCameraController() = delete;
  FirstPersonCameraController(Entity* pOwnerEntity, Component* pOwnerComponent) :
    Script(pOwnerEntity, pOwnerComponent, UNDEFINED, Component::eType::SCRIPT),
    _isDragingOn(false),
    _moveSpeed(5.0f),
    _up(Vector3f(0.0f, 1.0f, 0.0f)),
    _firstPersonTurnSpeed(0.01f),
    _editorModeTurnSpeed(0.05f),
    _isFirstPerson(false)
  {}
  virtual ~FirstPersonCameraController() noexcept {}


  /**
   * Initialize this script
   *
   * Called once when parent Entity is being initialized.
   */
  virtual void OnInitializeScene()
  {
    _yaw = GetTransformPtr()->GetRotation().GetX();
    _pitch = GetTransformPtr()->GetRotation().GetY();
  }

  void SetBallPtr(Rigidbody* pBody)
  {
    _pBall = pBody;
  }


  /**
   * Do all things you need to do in each frame
   *
   * Called once per frame.
   */
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene)
  {
    UNREFERENCED_PARAMETER(deltaTime);
    UNREFERENCED_PARAMETER(pScene);

    // Process switching key
    if (pScene->GetInputManagerPtr()->IsOnKeyboardKeyDown(INPUT_KEY_F3))
    {
      // Toggle 
      _isFirstPerson = !_isFirstPerson;
    }


    // If normal play camera mode
    if (!_isFirstPerson)
    {
      if (_pBall != nullptr)
      {
        // Do action camera
        ProcessActionCamera(deltaTime, pScene);
      }
    }
    // If free first person
    else
    {
      ProcessKeyControl(deltaTime, pScene);
      ProcessMouseControl(pScene);
      ProcessMouseKeyControl(pScene);
    }
           
  }

  void ProcessActionCamera(dfloat deltaTime, Scene* pScene)
  {
    UNREFERENCED_PARAMETER(deltaTime);
    UNREFERENCED_PARAMETER(pScene);

    dfloat _actionCamRotateCoef = 0.30f; _actionCamRotateCoef;

    glm::vec3 pos = GetTransformPtr()->GetPosition().GetData();

    // Get where ball is right now
    glm::vec3 aa((pos - _pBall->GetTransformPtr()->GetPosition().GetData()));

    glm::vec3 camToBallDir = glm::normalize(aa);
    glm::vec3 camDir = glm::normalize(GetTransformPtr()->GetZDir().GetData());
    camDir.z = -camDir.z;
    

    glm::mat4 lookTrans = glm::lookAt(pos, _pBall->GetTransformPtr()->GetPosition().GetData(), _up.GetData());

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(lookTrans, scale, rotation, translation, skew, perspective);

    

    glm::vec3 rot = glm::eulerAngles(rotation);

    Vector3f roooot((rot.y) *_actionCamRotateCoef + _yaw, (-rot.x) *_actionCamRotateCoef + _pitch - 0.2f, (rot.z) *_actionCamRotateCoef);
    
    // Update Transform values
    GetTransformPtr()->SetRotation(roooot);
  }


  void ProcessKeyControl(dfloat deltaTime, Scene* pScene)
  {
    Vector3f position = GetTransformPtr()->GetPosition();
    _frontDirection = GetTransformPtr()->GetZDir();
    _left = GetTransformPtr()->GetXDir();
    _up = GetTransformPtr()->GetYDir();


    dfloat deltaSpeed = _moveSpeed * deltaTime;

    if (pScene->GetInputManagerPtr()->IsOnKeyboardKeyDown(INPUT_KEY_K))
    {
      _mode = eCameraMode::EDITOR_CAMERA;
      _pOwnerEntity->GetOwnerScenePtr()->GetMainWindowPtr()->ShowCursor();
    }

    if (pScene->GetInputManagerPtr()->IsOnKeyboardKeyDown(INPUT_KEY_L))
    {
      _mode = eCameraMode::NORMAL;
      _pOwnerEntity->GetOwnerScenePtr()->GetMainWindowPtr()->HideCursor();
    }


    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_W))
    {
      position = position + _frontDirection * deltaSpeed;
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_S))
    {
      position = position - (_frontDirection * deltaSpeed);
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_A))
    {
      position = position + (_left * deltaSpeed);
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_D))
    {
      position = position - (_left * deltaSpeed);
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_SPACE) && !pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_LEFT_SHIFT))
    {
      position = position + (_up * deltaSpeed);
    }

    if (pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_SPACE) && pScene->GetInputManagerPtr()->IsKeyboardKeyDown(INPUT_KEY_LEFT_SHIFT))
    {
      position = position - (_up * deltaSpeed);
    }

    // Update position in Transform Component
    GetTransformPtr()->SetPosition(position);
  }

  void ProcessMouseControl(Scene* pScene)
  {
    int xChange = pScene->GetInputManagerPtr()->GetMouseXDelta(); 
    int yChange = pScene->GetInputManagerPtr()->GetMouseYDelta();

    _mouseXChange = xChange;
    _mouseYChange = yChange;

    dfloat firstPersonChangeX = xChange * _firstPersonTurnSpeed;
    dfloat firstPersonChangeY = yChange * _firstPersonTurnSpeed;

    //dfloat editorModeChangeX = xChange * _editorModeTurnSpeed;
    //dfloat editorModeChangeY = yChange * _editorModeTurnSpeed;

    Vector3f rotationAngles = GetTransformPtr()->GetRotation();

    dfloat yaw = rotationAngles.GetX() + firstPersonChangeX;
    dfloat pitch = rotationAngles.GetY() + firstPersonChangeY;

    // Limit pitch angle
    if (pitch > static_cast<dfloat>(M_PI_2))
    {
      pitch = static_cast<dfloat>(M_PI_2);
    }

    if (pitch < static_cast<dfloat>(-(M_PI_2- 0.1)))
    {
      pitch = static_cast<dfloat>(-(M_PI_2 - 0.1));
    }

    rotationAngles.SetX(yaw);
    rotationAngles.SetY(pitch);

    // Update Transform values
    GetTransformPtr()->SetRotation(rotationAngles);
    
  }

  void ProcessMouseKeyControl(Scene* pScene)
  {

    if (pScene->GetInputManagerPtr()->IsMouseKeyDown(INPUT_MOUSE_BUTTON_RIGHT))
    {
      _isDragingOn = true;
    }
    else
    {
      _isDragingOn = false;
    }
  }

  glm::mat4 CalculateViewMatrix()
  {
    return glm::lookAt(GetTransformPtr()->GetPosition().GetData(), (GetTransformPtr()->GetPosition() + _frontDirection).GetData(), _up.GetData());
  }

private:
  eCameraMode _mode;

  Vector3f _frontDirection;
  Vector3f _up;
  Vector3f _left;
  Vector3f _worldUp;

  int _mouseXChange;
  int _mouseYChange;

  dfloat _yaw;
  dfloat _pitch;
  dfloat _inverseYaw;
  dfloat _inversePitch;

  bool _isFirstPerson;

  dfloat _moveSpeed;
  dfloat _firstPersonTurnSpeed;
  dfloat _editorModeTurnSpeed;
  bool _isDragingOn;

  Rigidbody* _pBall;
};

};
  