#include "Controller.h"

using namespace SYE;

Controller::Controller(std::shared_ptr<Entity> pEntity) :
  Component(pEntity)
{

}

Controller::~Controller()
{}
