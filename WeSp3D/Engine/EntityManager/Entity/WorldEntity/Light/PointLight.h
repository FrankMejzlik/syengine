#pragma once

#include <vector>

#include "Light.h"
#include "OmniShadowMap.h"

using namespace WeSp;

namespace WeSp 
{

class PointLight :
  public Light
{
public:
  PointLight();
  PointLight(
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 colourVector,
    glm::vec3 lightIntensities,
    glm::vec3 shadowDimensions,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients
  );
  virtual ~PointLight();

  virtual void UseLight(
    GLuint ambientIntensityLocation,
    GLuint ambientColourLocation,
    GLuint diffuseIntensityLocation,
    GLuint positionLocation,
    GLuint constantLocation,
    GLuint linearLocation,
    GLuint exponentLocation
  );

  std::vector<glm::mat4> GetOmniLightModelToWorldMatrices();

  glm::vec3 GetPosition();
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