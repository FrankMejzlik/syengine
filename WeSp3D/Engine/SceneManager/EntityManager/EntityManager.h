#pragma once

#include "common.h"
#include "BaseModule.h"
#include "ComponentManager.h"
#include "Entity.h"

#include "Primitive\Quad.h"


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

using namespace WeSp;

namespace WeSp {

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
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    dfloat width, dfloat height
  );


private:

};

}