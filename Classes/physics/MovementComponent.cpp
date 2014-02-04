#include "MovementComponent.h"

namespace Physics
{
char* MovementComponent::COMPONENT_TYPE;

MovementComponent::MovementComponent()
{
}

MovementComponent::~MovementComponent()
{
}

MovementComponent* MovementComponent::create(Point acceleration, Point gravity)
{
	return 0;
}

Point MovementComponent::getSpeed()
{
	return 0;
}

Point MovementComponent::getDirection()
{
	return 0;
}

Point MovementComponent::getAcceleration()
{
	return 0;
}

Point MovementComponent::getGravity()
{
	return 0;
}

void MovementComponent::setSpeed(Point speed)
{
}

void MovementComponent::setDirection(Point direction)
{
}

void MovementComponent::setAcceleration(Point acceleration)
{
}

void MovementComponent::setGravity(Point gravity)
{
}

boolean MovementComponent::isStarting()
{
	return 0;
}

boolean MovementComponent::init()
{
	return 0;
}

void MovementComponent::initListeners()
{
}

void MovementComponent::onEditMove(EventCustom* pEvent)
{
}

void MovementComponent::onJump(EventCustom* pEvent)
{
}

void MovementComponent::onInterruptMove(EventCustom* pEvent)
{
}

void MovementComponent::update(float fDt)
{
}
}  // namespace Physics
