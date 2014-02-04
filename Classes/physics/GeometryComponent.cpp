/* *****************************************************
 *		GeometryComponent.cpp - @ Flora Jullien - 30/01/14
 ***************************************************** */

#include "core/SynthActor.h"
#include "GeometryComponent.h"
#include "events/ChangePositionEvent.h"

const char* GeometryComponent::COMPONENT_TYPE = "GeometryComponent";

GeometryComponent::GeometryComponent()
	: SynthComponent() {

}

GeometryComponent::~GeometryComponent() {

}

bool GeometryComponent::init() {
	return SynthComponent::init(GeometryComponent::COMPONENT_TYPE);
}

GeometryComponent* GeometryComponent::create(Point position) {
	GeometryComponent* pRet = new GeometryComponent();
	if (pRet != nullptr && pRet->init()) {
		pRet->autorelease();
		pRet->_position = position;
	} else { 
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void GeometryComponent::initListeners() {
	_pChangePositionListener = EventListenerCustom::create(ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(GeometryComponent::onChangePosition, this));
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangePositionListener, 1);
}

void GeometryComponent::onChangePosition(EventCustom* pEvent) {
	ChangePositionEvent* pChangePosEvent = static_cast<ChangePositionEvent*>(pEvent);
	SynthActor* pOwner = static_cast<SynthActor*>(_owner);
	SynthActor* pEventSource = static_cast<SynthActor*>(pChangePosEvent->getSource());
	if (pOwner->getActorID() == pEventSource->getActorID()) {
		_position = pChangePosEvent->getCurrentPosition();
	}
}