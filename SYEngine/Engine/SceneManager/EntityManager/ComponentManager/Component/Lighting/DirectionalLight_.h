#pragma once

#include "Light_.h"

using namespace SYE;

namespace SYE 
{

/**
 * Light that is in infinite distance. It has direction.
 */
class DirectionalLight :
  public Light
{
public:
  DirectionalLight() = delete;
  DirectionalLight(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept;
  virtual ~DirectionalLight() noexcept;
  
  glm::vec3 GetLightDirection() const { return _lightDirectionVector; };
  void SetLightDirection(glm::vec3 lightDirection) { _lightDirectionVector = lightDirection; };
  
  void UseLight(
    GLuint ambientIntensityLocation, 
    GLuint ambientColourLocation,
    GLuint diffuseIntensityLocation, 
    GLuint directionLocation
  );

  // Calculates matrix to transform world to "POV of this light"
  glm::mat4 CalculateLightTransformMatrix();

protected:
  // Direction of light
  glm::vec3 _lightDirectionVector;
};

}