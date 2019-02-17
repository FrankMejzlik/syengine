#include "Sound.h"

using namespace SYE;

Sound::Sound(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) :
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots)
{
  _type = eType::SOUND;
}


Sound::~Sound()
{}
