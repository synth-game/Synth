/*!
 * \file MovementComponent.cpp
 * \brief Main manager, the entry point of our program
 * \author Flora Jullien
 * \date 12/02/2014
 */
#include "MovementComponent.h"
#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "events/InterruptMoveEvent.h"
#include "core/SynthActor.h"

namespace physics {

const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";

MovementComponent::MovementComponent()
	: SynthComponent(), _pEditMoveEventListener(nullptr), _pJumpEventListener(nullptr), _pInterruptMoveEventListener(nullptr) {

}

MovementComponent::~MovementComponent() {

}

MovementComponent* MovementComponent::create(Point acceleration, Point gravity) {
    MovementComponent* pMovementComponent = new MovementComponent();
	if (pMovementComponent != nullptr && pMovementComponent->init()) {
		pMovementComponent->autorelease();
		pMovementComponent->setAcceleration(acceleration);
		pMovementComponent->setGravity(gravity);
	} else {
		CC_SAFE_DELETE(pMovementComponent);
	}
	return pMovementComponent;
}

bool MovementComponent::init() {
	SynthComponent::init(MovementComponent::COMPONENT_TYPE);
	return true;
}

void MovementComponent::initListeners() {
	_pEditMoveEventListener = EventListenerCustom::create(events::EditMoveEvent::sEventName, CC_CALLBACK_1(MovementComponent::onEditMove, this));
	_pJumpEventListener = EventListenerCustom::create(events::JumpEvent::sEventName, CC_CALLBACK_1(MovementComponent::onJump, this)); 
	_pInterruptMoveEventListener = EventListenerCustom::create(events::InterruptMoveEvent::sEventName, CC_CALLBACK_1(MovementComponent::onInterruptMove, this));
}

void MovementComponent::onEditMove(EventCustom* pEvent) {
	events::EditMoveEvent* editMoveEvent = static_cast<events::EditMoveEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(editMoveEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		if (editMoveEvent->getChangeX()) {
			_direction.x = editMoveEvent->getDirection().x;
		}
		if (editMoveEvent->getChangeY()) {
			_direction.y = editMoveEvent->getDirection().y;
		}
		_bStartMoving = editMoveEvent->isStartMoving();
	}
}

void MovementComponent::onJump(EventCustom* pEvent) {
	events::JumpEvent* jumpEvent = static_cast<events::JumpEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(jumpEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		
	}
}

void MovementComponent::onInterruptMove(EventCustom* pEvent) {
	events::InterruptMoveEvent* interruptMoveEvent = static_cast<events::InterruptMoveEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(interruptMoveEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		
	}
}

void MovementComponent::update(float fDt) {

}

}  // namespace physics
