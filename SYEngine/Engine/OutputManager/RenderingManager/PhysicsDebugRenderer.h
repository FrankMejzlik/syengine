#pragma once


#include "LinearMath/btIDebugDraw.h"

#include "common.h"
#include <GL/glew.h>
#pragma warning(push, 1)
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#pragma warning(pop)


namespace SYE
{

class PhysicsDebugRenderer:
  public btIDebugDraw
{
public:
  virtual void setDebugMode(int debugMode) override { _debugMode = debugMode; }
  virtual int getDebugMode() const override { return _debugMode; }

  virtual void  drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) override;
  virtual void  drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override;

  virtual void  reportErrorWarning(const char* warningString) override;
  virtual void  draw3dText(const btVector3& location, const char* textString) override;

  void SetMatrices(size_t shaderId, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

  void ToggleDebugFlag(int flag);

protected:
  int _debugMode;

  GLuint VBO;
  GLuint VAO;
};

}
