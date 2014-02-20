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
#include "events/ChangePositionEvent.h"
#include "events/TestCollisionEvent.h"
#include "core/SynthActor.h"
#include "physics/GeometryComponent.h"
#include "physics/CollisionComponent.h"

#define MAX_X_SPEED 200.f
#define MAX_Y_SPEED 300.f
#define MAX_JUMP_SPEED 300.f
#define MIN_JUMP_SPEED 150.f

namespace physics {

const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";

MovementComponent::MovementComponent()
	: SynthComponent(), _pEditMoveEventListener(nullptr), _pJumpEventListener(nullptr), _pInterruptMoveEventListener(nullptr) {
		_bStartMoving = false;
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
	// Listeners initialization
	_pEditMoveEventListener = EventListenerCustom::create(events::EditMoveEvent::EVENT_NAME, CC_CALLBACK_1(MovementComponent::onEditMove, this));
	_pJumpEventListener = EventListenerCustom::create(events::JumpEvent::EVENT_NAME, CC_CALLBACK_1(MovementComponent::onJump, this)); 
	_pInterruptMoveEventListener = EventListenerCustom::create(events::InterruptMoveEvent::EVENT_NAME, CC_CALLBACK_1(MovementComponent::onInterruptMove, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEditMoveEventListener, 1);
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
	// compute next speed
	//_speed = _speed + Point(_direction.x * _acceleration.x, _direction.y * _acceleration.y) + _gravity;
	_speed = _speed + Point(_direction.x * _acceleration.x, _direction.y * _acceleration.y);
    
    CCLOG("direction %2.f, %2.f", _direction.x, _direction.y);
	// cap the next lateral speed
	if (_bStartMoving) {
		CCLOG("YES");
		if (abs(_speed.x) > MAX_X_SPEED) {
			_speed.x = _direction.x * MAX_X_SPEED;
		}
	} else {
		CCLOG("NOT");
		if (_speed.x * _direction.x > 0.f) {
			_speed.x = 0.f;
		}
	}

	if (_speed.y < - MAX_Y_SPEED) {
		_speed.y = -MAX_Y_SPEED;
	}
	if (_speed.y > MAX_Y_SPEED) {
		_speed.y = MAX_Y_SPEED;
	}

	// compute next position
	physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pGeometryComponent != nullptr, "MovementComponent needs a GeometryComponent added to its owner");

	Point nextPosition = pGeometryComponent->getPosition() + (_speed * fDt);
	CCLOG("speed %2.f, %2.f", _speed.x, _speed.y);
	nextPosition.x = floor(nextPosition.x);
	nextPosition.y = floor(nextPosition.y);

	physics::CollisionComponent* pCollisionComponent = static_cast<physics::CollisionComponent*>(_owner->getComponent(physics::CollisionComponent::COMPONENT_TYPE));
	if (pCollisionComponent == nullptr) {
		//CCLOG("envoie evenemnt, position %2.f, %2.f", nextPosition.x, nextPosition.y);
		events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, nextPosition);
		EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
	} else {
		events::TestCollisionEvent* pTestCollisionEvent = new events::TestCollisionEvent(_owner, pGeometryComponent->getPosition(), nextPosition, pGeometryComponent->getSize());
		EventDispatcher::getInstance()->dispatchEvent(pTestCollisionEvent);
	}
}

}  // namespace physics
