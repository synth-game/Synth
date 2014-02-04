#include "LightSwitchSoundComponent.h"

namespace Sounds
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
}  // namespace Sounds
