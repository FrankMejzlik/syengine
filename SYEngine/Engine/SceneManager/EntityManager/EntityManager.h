#pragma once

#include "common.h"
#include "BaseModule.h"
//#include "Scene.h"
#include "ComponentManager.h"
#include "Entity.h"

#include "Primitive\Quad.h"
#include "Primitive\Block.h"

#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Camera.h"





enum class eEntityType
{
  ENTITY,
    SCREEN_ENTITY,
    WORLD_ENTITY,
      CAMEREA,
      LIGHT,
        DIRECTIONAL_LIGHT,
        POINT_LIGHT,
        SPOT_LIGHT,
      WORLD_OBJECT,
        PRIMITIVE,
          QUAD
      
};

using namespace SYE;

namespace SYE {

class EntityManager :
  public BaseModule
{
public:
  EntityManager() = delete;

  EntityManager(BaseModule &parentModule);
  ~EntityManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  
  Entity* CreateCamera(std::string_view cameraName, glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch, float turnSpeed, float moveSpeed);

  Entity* CreateQuad(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height
  );
  Entity* CreateBlock(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height, dfloat length,
    bool bIsStatic
  );

  Entity* CreateStaticModelFromFile(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    std::string_view filePath
  );

  Entity* CreateDirectionalLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour, glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec3 lightDirection
  );

  Entity* CreatePointLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour,
    glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients
  );

  Entity* CreateSpotLight(
    std::string_view entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 lightColour,
    glm::vec3 lightIntensities,
    glm::vec3 shadowMapSize,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients,
    glm::vec3 lightDirection,
    dfloat coneAngle
  );

protected:
private:
  Entity* InsertEntity(std::unique_ptr<Entity>&& pNewEntity);


private:
  std::map<size_t, std::unique_ptr<Entity>> _entityList;
};

}