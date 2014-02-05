/* *****************************************************
 *      MovementComponent.cpp - @ Jeremie Defaye - 02/02/14
 ***************************************************** */

#include "MovementComponent.h"
#include "GeometryComponent.h"

namespace physics
{
const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";

MovementComponent::MovementComponent()
    : SynthComponent() {

}

MovementComponent::~MovementComponent()
{
}

MovementComponent* MovementComponent::create(Point gravity) {
    MovementComponent* pRet = new MovementComponent();
    if (pRet != nullptr && pRet->init()) {
        pRet->autorelease();
        pRet->_speed = Point::ZERO;
        pRet->_gravity = gravity;
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
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

bool MovementComponent::isStarting()
{
	return 0;
}

bool MovementComponent::init() {
    return SynthComponent::init(MovementComponent::COMPONENT_TYPE);
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
    // update speed
    _speed = _speed + _gravity;
    // get current position
    GeometryComponent* pGeometryComp = static_cast<GeometryComponent*>(_owner->getComponent(GeometryComponent::COMPONENT_TYPE));
    CCASSERT(pGeometryComp != nullptr, "MovementComponent need a GeometryComponent added to its owner");
    Point currentPos = pGeometryComp->getPosition();

    //compute next position
    Point nextPos = currentPos + (_speed*fDt);

    //send event to update position
    //TODO
}
}  // namespace physics
