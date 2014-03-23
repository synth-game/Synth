#include "FlyMovementComponent.h"
#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "Events/InterruptMoveEvent.h"
#include "Events/ChangeStateEvent.h"
#include "physics/GeometryComponent.h"
#include "physics/CollisionComponent.h"
#include "events/ChangePositionEvent.h"
#include "events/ChangeStateEvent.h"

#define MAX_X_SPEED 200.f
#define MAX_Y_SPEED 200.f

namespace physics
{

FlyMovementComponent::FlyMovementComponent()
	: MovementComponent(){
}

FlyMovementComponent::~FlyMovementComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pEditMoveEventListener);
    EventDispatcher::getInstance()->removeEventListener(_pJumpEventListener);
	EventDispatcher::getInstance()->removeEventListener(_pInterruptMoveEventListener);
    EventDispatcher::getInstance()->removeEventListener(_pChangeStateEventListener);
}

void FlyMovementComponent::onEnter() {
	events::ChangeStateEvent* pEvent = new events::ChangeStateEvent(_owner, core::ActorState::ON_AIR_STATE);
	EventDispatcher::getInstance()->dispatchEvent(pEvent);
	delete pEvent;
}

FlyMovementComponent* FlyMovementComponent::create(Point acceleration) {

	FlyMovementComponent* pFlyMovementComponent = new FlyMovementComponent();
	if (pFlyMovementComponent != nullptr && pFlyMovementComponent->init()) {
		pFlyMovementComponent->autorelease();
		pFlyMovementComponent->setAcceleration(acceleration);
	} else {
		CC_SAFE_DELETE(pFlyMovementComponent);
	}
	return pFlyMovementComponent;
}

bool FlyMovementComponent::init() {
	SynthComponent::init(MovementComponent::COMPONENT_TYPE);
	return true;
}

void FlyMovementComponent::initListeners() {
	// Listeners initialization
	_pEditMoveEventListener = EventListenerCustom::create(events::EditMoveEvent::EVENT_NAME, CC_CALLBACK_1(FlyMovementComponent::onEditMove, this));
	_pJumpEventListener = EventListenerCustom::create(events::JumpEvent::EVENT_NAME, CC_CALLBACK_1(FlyMovementComponent::onJump, this));
	_pInterruptMoveEventListener = EventListenerCustom::create(events::InterruptMoveEvent::EVENT_NAME, CC_CALLBACK_1(FlyMovementComponent::onInterruptMove, this));
	_pChangeStateEventListener = EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(FlyMovementComponent::onChangeState, this));

	// Add listeners to dispacadr
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEditMoveEventListener, 1);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pJumpEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pInterruptMoveEventListener, 1);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeStateEventListener, 1);
}

void FlyMovementComponent::onEditMove(EventCustom* pEvent) {
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

void FlyMovementComponent::onJump(EventCustom* pEvent) {
	// DO NOTHING
}

void FlyMovementComponent::update(float fDt) {
	// compute next speed
	_speed = _speed + Point(_direction.x * _acceleration.x, _direction.y * _acceleration.y) /*+ _gravity*/;

	if ( !(_direction.x < 0.1f && _direction.x > -0.1f) && (_direction.y < 0.1f && _direction.y > -0.1f)){
		_speed.y = 0;
	}
	if ( !(_direction.y < 0.1f && _direction.y > -0.1f) && (_direction.x < 0.1f && _direction.x > -0.1f)){
		_speed.x = 0;
	}

	if (!_bStartMoving){
		if(_speed.x > 0){
			_speed.x -= _acceleration.x;
		} else if (_speed.x < 0){
			_speed.x += _acceleration.x;
		}

		if(_speed.y > 0){
			_speed.y -= _acceleration.y;
		} else if (_speed.y < 0){
			_speed.y += _acceleration.y;
		}
	}

	// cap the next lateral speed
	if (_bStartMoving) {

		if (abs(_speed.x) > MAX_X_SPEED) {
			_speed.x = _direction.x * MAX_X_SPEED;
		}
		if (abs(_speed.y) > MAX_Y_SPEED) {
			_speed.y = _direction.y * MAX_Y_SPEED;
		}
	} /* else {

		if (_speed.x * _direction.x > 0.f) {
			_speed.x = 0.f;
		}
		if (_speed.y * _direction.y > 0.f) {
			_speed.y = 0.f;
		}
	}*/

	// compute next position
	physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pGeometryComponent != nullptr, "MovementComponent needs a GeometryComponent added to its owner");
	Point nextPosition = pGeometryComponent->getPosition() + (_speed * fDt);

	nextPosition.x = floor(nextPosition.x);
	nextPosition.y = floor(nextPosition.y);

	physics::CollisionComponent* pCollisionComponent = static_cast<physics::CollisionComponent*>(_owner->getComponent(physics::CollisionComponent::COMPONENT_TYPE));
	if (pCollisionComponent == nullptr) {
		//CCLOG("envoie evenemnt, position %2.f, %2.f", nextPosition.x, nextPosition.y);
		events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, nextPosition);
		EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
		delete pChangePositionEvent;
	} else {
		events::TestCollisionEvent* pTestCollisionEvent = new events::TestCollisionEvent(_owner, pGeometryComponent->getPosition(), nextPosition, pGeometryComponent->getSize());
		EventDispatcher::getInstance()->dispatchEvent(pTestCollisionEvent);
		delete pTestCollisionEvent;
	}
}

}  // namespace physics
