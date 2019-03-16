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
  const glm::mat4& dc_GetOrthoProjectionMatrixConstRef();
  const glm::mat4& dc_GetPerspectiveProjectionMatrixConstRef();

  Vector3f GetPickingRay(int x, int y);
  
  void SetFov(dfloat fovAngle) { _fov = fovAngle; }
  dfloat GetFov() const { return _fov; }

  void SetCameraMode(eCameraModes mode) { _mode = mode; }
  
  void SetCameraPosition(Vector3f position);
  void SetCameraDirection(Vector3f direction);
  Vector3f GetCameraPosition() const;
  Vector3f GetCameraDirection() const;


  const Matrix4f& GetOrthogonalProjectionMatrix() const;
  void SetOrthogonalProjectionMatrix(Matrix4f matrix);
  void SetTargetWindow(Window* pWindow);
  void SetTargetTexture(const Texture* pTexture);


private:
  void dc_CalculateViewMatrix();
  void dc_CalculateOrthoProjectionMatrix();
  void dc_CalculatePerspectiveProjectionMatrix();
  


  // Attributes
protected:
  //! Window instance this Camera is working for
  Window* _pTargetWindow;

  //! Target texture this Camera is working for
  const Texture* _pTargetTexture;

  Matrix4f _orthogonalProjectionMatrix;
  Matrix4f _perspectiveProjectionMatrix;

  

  //! Current view matrix for this Camera
  glm::mat4 _dc_viewMatrix;
  
  //! Orthogonal projection matrix for this Camera
  glm::mat4 _dc_orthoProjectionMatrix;

  //! Perspective projection matrix for this Cmaera
  glm::mat4 _dc_perspectiveProjectionMatrix;

  //! True if calculated matrix is up to date and calculated
  bool _isOrthoProjectionMatrixCalculated;

  //! True if calculated matrix is up to date and calculated
  bool _isPerspectiveProjectionMatrixCalculated;

  //! World up direction
  Vector3f _upDirection;

  //! Camera mode it is currently in
  eCameraModes _mode;

  //! Field of View of this Camera 
  dfloat _fov;

  //! Near plane distance
  dfloat _nearPlane;

  //! Far plane distance
  dfloat _farPlane;

};

}