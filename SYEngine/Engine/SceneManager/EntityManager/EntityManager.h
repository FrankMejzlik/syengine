#pragma once

#include "common.h"
#include "BaseModule.h"
//#include "Scene.h"
#include "ComponentManager.h"
#include "Entity.h"

#include "Primitive\Quad.h"
#include "Primitive\Block.h"




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


  std::shared_ptr<Quad> CreateQuad(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height
  );
  std::shared_ptr<Block> CreateBlock(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height, dfloat length
  );

  std::shared_ptr<WorldObject> CreateStaticModelFromFile(
    std::string entityName,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    std::string filePath
  );


private:
  std::map<std::string, std::shared_ptr<Entity>> _entityList;
};

}