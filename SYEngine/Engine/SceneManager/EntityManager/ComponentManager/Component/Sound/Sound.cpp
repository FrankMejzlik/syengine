#include "Sound.h"

using namespace SYE;

Sound::Sound(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) :
  Component(pOwnerEntity, subModulesConstRef)
{
  _type = eType::SOUND;
}


Sound::~Sound()
{}
