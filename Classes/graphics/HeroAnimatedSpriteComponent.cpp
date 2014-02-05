#include "HeroAnimatedSpriteComponent.h"

namespace graphics
{

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent()
{
}

HeroAnimatedSpriteComponent::~HeroAnimatedSpriteComponent()
{
}

HeroAnimatedSpriteComponent* HeroAnimatedSpriteComponent::create()
{
	return 0;
}

void HeroAnimatedSpriteComponent::initListeners()
{
}

void HeroAnimatedSpriteComponent::onChangePosition(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onEditMove(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onJump(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onInterruptMove(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onChangeNodeOwner(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onToggleLight(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onDeath(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onWin(EventCustom* pEvent)
{
}

void HeroAnimatedSpriteComponent::onResetLevel(EventCustom* pEvent)
{
}
}  // namespace graphics
