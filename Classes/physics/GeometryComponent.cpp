/*!
 * \file GeometryComponent.h
 * \brief Class giving a position, a size, a rotation angle and an anchorpoint to the SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#include "GeometryComponent.h"
#include "events/ChangePositionEvent.h"
#include "core/SynthActor.h"

namespace physics {

const char* GeometryComponent::COMPONENT_TYPE = "GeometryComponent";

GeometryComponent::GeometryComponent()
    : SynthComponent() {
}

GeometryComponent::~GeometryComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pChangePositionListener);
}

bool GeometryComponent::init() {
	SynthComponent::init(GeometryComponent::COMPONENT_TYPE);
	return true;
}

GeometryComponent* GeometryComponent::create(Point position, Size size, float fRotationAngle, Point anchorPoint) {
	GeometryComponent* pRet = new GeometryComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
		pRet->_position =			position;
		pRet->_size =				size;
		pRet->_fRotationAngle =		fRotationAngle;
		pRet->_anchorPoint =		anchorPoint;
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void GeometryComponent::initListeners() {
	_pChangePositionListener = cocos2d::EventListenerCustom::create(events::ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(GeometryComponent::onChangePosition, this));
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangePositionListener, 1);
}

void GeometryComponent::onChangePosition(EventCustom* pEvent) {
    //CCLOG("GeometryComponent::onChangePosition CHANGE POSITION RECEIVED");
	events::ChangePositionEvent* changePositionEvent = static_cast<events::ChangePositionEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(changePositionEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		_position = changePositionEvent->getCurrentPosition();
	}
}

void GeometryComponent::onEnter() {
	
}


}  // namespace physics
