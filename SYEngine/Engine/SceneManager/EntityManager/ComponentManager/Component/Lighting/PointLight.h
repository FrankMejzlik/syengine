#pragma once

#include <vector>

#include "Light.h"
#include "OmniShadowMap.h"
#include "MathLibrary.h"

using namespace SYE;

namespace SYE 
{

class PointLight :
  public Light
{
public:
  PointLight() = delete;
  PointLight(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    eSlotIndex slotIndex = POINT_LIGHT_SOURCE, Component::eType type = eType::POINT_LIGHT
  ) ;
  virtual ~PointLight() noexcept;
  

  void SetShadowDimensions(glm::ivec3 shadowDimensions, dfloat nearPlane, dfloat farPlane);
  void SetCoeficients(Vector3f coefficients);
  

  virtual void UseLight(
    GLuint ambientIntensityLocation,
    GLuint ambientColourLocation,
    GLuint diffuseIntensityLocation,
    GLuint positionLocation,
    GLuint constantLocation,
    GLuint linearLocation,
    GLuint exponentLocation
  );

  Vector3f GetPosition() const;

  std::vector<glm::mat4> GetOmniLightModelToWorldMatrices();

  GLfloat GetFarPlane();

protected:
  // To control light attenuation
  // By setting those, we control how light intensity 
  // is reduced with increasing distance form light source

  // L / (ax^2 + bx + c)
  GLfloat _constant, _linear, _exponent;

  // How far camera can see
  GLfloat _farPlane;
  GLfloat _nearPlane;

};

}