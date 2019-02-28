#include "MotionState.h"

using namespace SYE;

MotionState::MotionState(const btTransform &transform) noexcept : 
  btDefaultMotionState(transform) 
{}


MotionState::~MotionState() noexcept
{}

void MotionState::GetWorldTransform(btScalar* transform) 
{
  btTransform trans;
  getWorldTransform(trans);
  trans.getOpenGLMatrix(transform);
}