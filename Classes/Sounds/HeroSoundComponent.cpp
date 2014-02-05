#include "HeroSoundComponent.h"

namespace sounds
{

HeroSoundComponent::HeroSoundComponent()
{
}

HeroSoundComponent::~HeroSoundComponent()
{
}

HeroSoundComponent* HeroSoundComponent::create()
{
	return 0;
}

void HeroSoundComponent::initListeners()
{
}

void HeroSoundComponent::onChangePosition(EventCustom* pEvent)
{
}

void HeroSoundComponent::onJump(EventCustom* pEvent)
{
}

void HeroSoundComponent::onInterruptMove(EventCustom* pEvent)
{
}

void HeroSoundComponent::onHeroDeath(EventCustom* pEvent)
{
}

void HeroSoundComponent::onPeriodicEvent(EventCustom* pEvent)
{
}
}  // namespace sounds
