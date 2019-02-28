#pragma once

#include "Light.h"

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
  DirectionalLight(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    eSlotIndex slotIndex = DIRECTIONAL_LIGHT_SOURCE, Component::eType type = eType::DIRECTIONAL_LIGHT
  );
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