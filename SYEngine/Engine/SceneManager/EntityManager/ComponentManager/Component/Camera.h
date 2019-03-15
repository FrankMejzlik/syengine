#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#undef APIENTRY

#pragma warning(push, 1)
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#pragma warning(pop)

#include "common.h"
#include "Component.h"


namespace SYE 
{

class Window;
class Transform;
class Texture;

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
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = CAMERA, Component::eType type = eType::CAMERA
  );

  const glm::mat4& GetViewMatrixConstRef();
  const glm::mat4& GetOrthoProjectionMatrixConstRef();
  const glm::mat4& GetPerspectiveProjectionMatrixConstRef();

  Vector3f GetPickingRay(int x, int y);
  
  void SetFov(dfloat fovAngle);
  dfloat GetFov() const;

  void SetCameraMode(eCameraModes mode) { _mode = mode; }
  
  Vector3f GetCameraPosition() const;
  Vector3f GetCameraDirection() const;

  void SetTargetWindow(Window* pWindow) 
  {
    _pTargetTexture = nullptr;
    _pTargetWindow = pWindow;

    _isPerspectiveProjectionMatrixCalculated = false;
  }
  void SetTargetTexture(const Texture* pTexture) 
  {
    _pTargetWindow = nullptr;
    _pTargetTexture = pTexture;

    _isPerspectiveProjectionMatrixCalculated = false;
  }

private:
  void CalculateViewMatrix();
  void CalculateOrthoProjectionMatrix();
  void CalculatePerspectiveProjectionMatrix();
  


  // Attributes
protected:
  /** Window instance this Camera is working for */
  Window* _pTargetWindow;



  const Texture* _pTargetTexture;

  /** Current view matrix for this Camera */
  glm::mat4 _viewMatrix;
  
  /** Orthogonal projection matrix for this Camera */
  glm::mat4 _orthoProjectionMatrix;

  /** Perspective projection matrix for this Cmaera */
  glm::mat4 _perspectiveProjectionMatrix;

  /** True if calculated matrix is up to date and calculated */
  bool _isOrthoProjectionMatrixCalculated;

  /** True if calculated matrix is up to date and calculated */
  bool _isPerspectiveProjectionMatrixCalculated;

  /** World up direction */
  // TODO: Globalize for all uses
  Vector3f _upDirection;

  /** Camera mode it is currently in */
  eCameraModes _mode;

  /** Field of View of this Camera */
  dfloat _fov;

  /** Near plane distance */
  dfloat _nearPlane;

  /** Far plane distance */
  dfloat _farPlane;

};

}