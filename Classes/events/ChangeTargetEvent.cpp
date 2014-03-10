/*!
 * \file ChangeTargetEvent.cpp
 * \brief Change the target of the follow movement
 * \author Chupee
 * \date 04/03/2014
 */
#include "ChangeTargetEvent.h"
#include "physics/GeometryComponent.h"

namespace events {

const char* ChangeTargetEvent::EVENT_NAME = "ChangeTargetEvent";

ChangeTargetEvent::ChangeTargetEvent(Node* pSource, core::SynthActor* newTarget) :
	SynthEvent(pSource, EVENT_NAME),
	_newTarget(newTarget) {
}

ChangeTargetEvent::ChangeTargetEvent(Node* pSource, Point newTarget) :
	SynthEvent(pSource, EVENT_NAME) {
		core::SynthActor* target = new core::SynthActor(core::ActorType::UNKNOWN_TYPE);
		target->addComponent(physics::GeometryComponent::create(newTarget, Size::ZERO, 0.f, Point::ZERO));
		_newTarget = target;
}

ChangeTargetEvent::~ChangeTargetEvent() {
}


}  // namespace events
