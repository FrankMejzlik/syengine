#pragma once

#pragma warning (push, 0)
  #include "btBulletCollisionCommon.h"
#pragma warning(pop)

class MotionState:
  public btDefaultMotionState
{
public:
  MotionState(const btTransform &transform) noexcept;
  virtual ~MotionState() noexcept;

  
  void GetWorldTransform(btScalar* transform);

};

