/* *****************************************************
 *		MovementComponent.cpp - @ Jeremie Defaye - 02/02/14
 ***************************************************** */

#include "MovementComponent.h"
#include "GeometryComponent.h"
#include "events/ChangePositionEvent.h"

const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";

MovementComponent::MovementComponent()
	: SynthComponent() {

}

MovementComponent::~MovementComponent() {

}

bool MovementComponent::init() {
	return SynthComponent::init(MovementComponent::COMPONENT_TYPE);
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

void MovementComponent::initListeners() {

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
	ChangePositionEvent* pChangePositionEvent = new ChangePositionEvent(_owner);
	pChangePositionEvent->setCurrentPosition(nextPos);
	EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
}