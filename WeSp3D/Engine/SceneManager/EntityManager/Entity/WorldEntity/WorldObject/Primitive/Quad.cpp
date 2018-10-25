#include "Quad.h"



Quad::Quad(
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  bool bIsStatic,
  glm::vec3 leftBottomCoordinate, glm::vec3 rightTopCoordinate
):
  WorldObject(positionVector, rotationVector, scaleVector, bIsStatic)
{}


Quad::~Quad()
{}
