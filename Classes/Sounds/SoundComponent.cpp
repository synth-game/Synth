#include "SoundComponent.h"

namespace sounds
{
char* SoundComponent::COMPONENT_TYPE;

SoundComponent::SoundComponent()
{
}

SoundComponent::~SoundComponent()
{
}

void SoundComponent::onSetStateEvent(EventCustom* pEvent)
{
}

bool SoundComponent::init()
{
	return false;
}
}  // namespace sounds
