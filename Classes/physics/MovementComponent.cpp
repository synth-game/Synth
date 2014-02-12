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

}

void MovementComponent::onJump(EventCustom* pEvent) {

}

void MovementComponent::onInterruptMove(EventCustom* pEvent) {

}

void MovementComponent::update(float fDt) {

}

}  // namespace physics
