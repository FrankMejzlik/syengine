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

  virtual void Refresh() override;

  void SetCameraMode(eCameraModes mode) { _mode = mode; }
  glm::mat4 CalculateViewMatrix();
  Vector3f GetCameraPosition() const;
  Vector3f GetCameraDirection() const;


protected:
  eCameraModes _mode;

private:
  // Quick refs
  Transform* _pTransform;

};

}