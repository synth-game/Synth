#include "LightSwitchSoundComponent.h"

namespace sounds
{

LightSwitchSoundComponent::LightSwitchSoundComponent()
{
}

LightSwitchSoundComponent::~LightSwitchSoundComponent()
{
}

LightSwitchSoundComponent* LightSwitchSoundComponent::create()
{
	return 0;
}

void LightSwitchSoundComponent::onToggleLight(EventCustom* pEvent)
{
}
}  // namespace sounds
