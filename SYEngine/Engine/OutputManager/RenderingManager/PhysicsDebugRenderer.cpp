#include "PhysicsDebugRenderer.h"

#include <GL/glew.h>


using namespace SYE;

#include <iostream>

void PhysicsDebugRenderer::SetMatrices(size_t shaderId, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) 
{
  glUniformMatrix4fv(glGetUniformLocation(static_cast<GLuint>(shaderId), "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
  glUniformMatrix4fv(glGetUniformLocation(static_cast<GLuint>(shaderId), "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void PhysicsDebugRenderer::drawLine([[maybe_unused]] const btVector3& from, [[maybe_unused]] const btVector3 &to, [[maybe_unused]] const btVector3 &color)
{

  // Vertex data
  GLfloat points[12];

  points[0] = from.x();
  points[1] = from.y();
  points[2] = from.z();
  points[3] = color.x();
  points[4] = color.y();
  points[5] = color.z();

  points[6] = to.x();
  points[7] = to.y();
  points[8] = to.z();
  points[9] = color.x();
  points[10] = color.y();
  points[11] = color.z();

  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glBindVertexArray(0);

  glBindVertexArray(VAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);

  
}

void PhysicsDebugRenderer::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, [[maybe_unused]] int lifeTime, const btVector3& color)
{

  // draws a line between two contact points
  btVector3 const startPoint = pointOnB;
  btVector3 const endPoint = pointOnB + normalOnB * distance;
  drawLine( startPoint, endPoint, color );
}

void PhysicsDebugRenderer::ToggleDebugFlag(int flag)
{
  // Checks if a flag is set and enables/disables it
  if (_debugMode & flag)
  {
    // Flag is enabled, so disable it
    _debugMode = _debugMode & (~flag);
  }
  else
  {
    // Flag is disabled, so enable it
    _debugMode |= flag;
  }
}

void PhysicsDebugRenderer::reportErrorWarning([[maybe_unused]] const char* warningString)
{

  LOG_NOT_IMPLEMENTED;
}

void PhysicsDebugRenderer::draw3dText([[maybe_unused]] const btVector3& location, [[maybe_unused]] const char* textString)
{

  LOG_NOT_IMPLEMENTED;
}