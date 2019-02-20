#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#undef APIENTRY

#pragma warning(push, 1)
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#pragma warning(pop)

#include "common.h"
#include "WorldEntity.h"


namespace SYE 
{
class Window;


class Camera:
  public Component
{
  // Structures
public:
  enum class eCameraModes
  {
    NORMAL, 
    EDITOR_CAMERA
  };


  // Methods
public:
	Camera() = delete;
	Camera(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
  ) noexcept;

  virtual void Refresh();

  void SetWorldUpDirection(Vector3f worldUp) { _worldUp = worldUp; }
  void SetYaw(dfloat yaw) { _yaw = yaw; }
  void SetPitch(dfloat pitch) { _pitch = pitch; }
  void SetCameraMode(eCameraModes mode) { _mode = mode; }
  void SetMoveSpeed(dfloat moveSpeed) { _moveSpeed = moveSpeed; }
  void SetIsDraggingOn(bool isDraggingOn) { _isDragingOn = isDraggingOn; }
  void SetTurnSpeed(dfloat turnSpeed) { _firstPersonTurnSpeed = turnSpeed; }

#if !INPUT_MANAGER_REFACTORED

  // TODO: Implement propperly Input in InputManager
  void KeyControl(Window* pMainWindow, dfloat deltaTime);
	void MouseControl(dfloat xChange, dfloat yChange);
  void MouseKeyControl(bool* keys, dfloat deltaTime);

#endif

	glm::mat4 CalculateViewMatrix();

  Vector3f GetCameraPosition() const;
  Vector3f GetCameraDirection() const;

protected:

  void Update();
  void UpdateEditorMode();
  void UpdateFirstPersonMode();
	

protected:
  eCameraModes _mode;

  Vector3f _frontDirection;
  Vector3f _up;
  Vector3f _right;
  Vector3f _worldUp;

  dfloat _mouseXChange;
  dfloat _mouseYChange;

	dfloat _yaw;
	dfloat _pitch;
  dfloat _inverseYaw;
  dfloat _inversePitch;


	dfloat _moveSpeed;
	dfloat _firstPersonTurnSpeed;
  dfloat _editorModeTurnSpeed;

  bool _isDragingOn;

private:
  // Quick refs
  Transform* _pTransform;

};

}