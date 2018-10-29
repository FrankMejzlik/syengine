#include "Controller.h"

using namespace WeSp;

Controller::Controller(std::shared_ptr<Entity> pEntity) :
  Component(pEntity)
{

}

Controller::~Controller()
{}
