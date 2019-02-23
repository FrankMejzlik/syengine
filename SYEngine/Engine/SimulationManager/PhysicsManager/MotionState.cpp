#include "MotionState.h"



MotionState::MotionState(const btTransform &transform) noexcept : 
  btDefaultMotionState(transform) 
{}


MotionState::~MotionState() noexcept
{}

void MotionState::GetWorldTransform(btScalar* transform) 
{
  btTransform trans;
  /*ADD*/			getWorldTransform(trans);
  /*ADD*/			trans.getOpenGLMatrix(transform);
}