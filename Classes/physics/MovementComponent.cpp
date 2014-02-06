#include "MovementComponent.h"

namespace physics
{
const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";

MovementComponent::MovementComponent()
    : SynthComponent() {

}

MovementComponent::~MovementComponent()
{
}

MovementComponent* MovementComponent::create(Point acceleration, Point gravity) {
    return nullptr;
}

Point MovementComponent::getSpeed()
{
	return Point::ZERO;
}

Point MovementComponent::getDirection()
{
	return Point::ZERO;
}

Point MovementComponent::getAcceleration()
{
	return Point::ZERO;
}

Point MovementComponent::getGravity()
{
	return Point::ZERO;
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

bool MovementComponent::isStarting()
{
	return false;
}

bool MovementComponent::init() {
	return false;
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

void MovementComponent::update(float fDt) {
}
}  // namespace physics
