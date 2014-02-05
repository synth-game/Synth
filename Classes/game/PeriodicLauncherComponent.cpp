#include "PeriodicLauncherComponent.h"

namespace game
{
char* PeriodicLauncherComponent::COMPONENT_TYPE;

PeriodicLauncherComponent::PeriodicLauncherComponent()
{
}

PeriodicLauncherComponent::~PeriodicLauncherComponent()
{
}

PeriodicLauncherComponent* PeriodicLauncherComponent::create(float fPeriod)
{
	return 0;
}

void PeriodicLauncherComponent::initListeners()
{
}

void PeriodicLauncherComponent::update(float fDt)
{
}

float PeriodicLauncherComponent::getPeriod()
{
	return 0;
}

void PeriodicLauncherComponent::setPeriod(float fPeriod)
{
}
}  // namespace game
