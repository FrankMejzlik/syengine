#pragma once

#include "common.h"
#include "BaseModule.h"

#include "ComponentManager.h"
#include "Entity.h"

#include "Primitive\Quad.h"
#include "Primitive\Block.h"

#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Camera.h"


#if !NEW_SSSEC_IMPLEMENTED
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
#endif

using namespace SYE;

namespace SYE 
{

class Scene;

class EntityManager :
  public BaseModule
{
public:
  EntityManager() = delete;

  EntityManager(BaseModule &parentModule);
  ~EntityManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  /**
   * Create empty new Entity instance
   *
   * New Entity instance is created. Entity is then
   * capable of attaching PRIMARY Components to itself.
   *
   * Entity can be either of type WORLD or SCREEN.
   * @param   Scene*    Pointer to Scene instance that will own this Entity.
   * @return  Entity*   Observer pointer to new Entity instance.
   *
   * @see   class Entity
   * @see   class ComponentManager
   * @see   class Component
   */
  Entity* CreateEntity(Scene* pOwnerScene);


protected:
private:
  Entity* InsertEntity(std::unique_ptr<Entity>&& pNewEntity);


private:
  std::map<size_t, std::unique_ptr<Entity>> _entities;


#if !NEW_SSSEC_IMPLEMENTED

public:
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

#endif

};

}