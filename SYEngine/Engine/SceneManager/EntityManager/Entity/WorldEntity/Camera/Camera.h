#pragma once

#include <GL\glew.h>

#pragma warning(push, 3)
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#pragma warning(pop)

#include <GLFW\glfw3.h>

#include "WorldEntity.h"


namespace SYE 
{
class Window;
enum class eCameraModes
{
  FIRST_PERSON_MODE, 
  EDITOR_MODE
};

class Camera:
  public WorldEntity
{
public:
	Camera() = delete;

	Camera(
    std::shared_ptr<ComponentManager> pComponentManager,
    glm::vec3 startPosition,
    glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed
  );
  ~Camera();

  void KeyControl(std::shared_ptr<Window> pMainWindow, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange);
  void MouseKeyControl(bool* keys, GLfloat deltaTime);

	glm::mat4 CalculateViewMatrix();

  glm::vec3 GetCameraPosition();
  glm::vec3 GetCameraDirection();

	

private:
  eCameraModes _eCameraMode;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

  dfloat _mouseXChange;
  dfloat _mouseYChange;

	GLfloat yaw;
	GLfloat pitch;
  dfloat _inverseYaw;
  dfloat _inversePitch;


	GLfloat _moveSpeed;
	GLfloat _firstPersonTurnSpeed;
  dfloat _editorModeTurnSpeed;

  bool _bIsDragingOn;

  void UpdateEditorMode();
	void UpdateFirstPersonMode();
};

}