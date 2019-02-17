#pragma once

#include "PointLight_.h"

using namespace SYE;

namespace SYE 
{

class SpotLight :
  public PointLight
{
public:
  SpotLight() = delete;
  SpotLight(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept;
  ~SpotLight() noexcept;

  void SetConeAngle(dfloat angle);
  void SetLightDirection(Vector3f direction);


  

  void UseLight(
    GLuint ambientIntensityLocation,
    GLuint ambientColourLocation,
    GLuint diffuseIntensityLocation,
    GLuint positionLocation,
    GLuint directionLocation,
    GLuint constantLocation,
    GLuint linearLocation,
    GLuint exponentLocation,
    GLuint edgeLocation
  );


private:
  GLfloat _coneAngle, _processedConeAngle;
  glm::vec3 _lightDirection;

};

}