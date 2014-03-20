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
#include "events/ChangeStateEvent.h"
#include "core/SynthActor.h"
#include "physics/GeometryComponent.h"
#include "physics/CollisionComponent.h"
#include "sounds/HeroSoundComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"

#define MAX_X_SPEED 200.f
#define MAX_Y_SPEED 400.f
#define MAX_JUMP_SPEED 400.f
#define MIN_JUMP_SPEED 100.f
#define ENGINE_SPEED 0.015

namespace physics {

const char* MovementComponent::COMPONENT_TYPE = "MovementComponent";

MovementComponent::MovementComponent()
	: SynthComponent()
	, _bStartMoving(false)
	, _eMovingState(core::ActorState::NOT_ON_FLOOR_STATE)
	, _pEditMoveEventListener(nullptr)
	, _pJumpEventListener(nullptr)
	, _pInterruptMoveEventListener(nullptr)
	, _pChangeStateEventListener(nullptr) {
}

MovementComponent::~MovementComponent() {
}
    
void MovementComponent::onExit() {
    CCLOG("MovementComponent::onExit : NEED TO REMOVE LISTENERS");
    EventDispatcher::getInstance()->removeEventListener(_pEditMoveEventListener);
    EventDispatcher::getInstance()->removeEventListener(_pJumpEventListener);
	EventDispatcher::getInstance()->removeEventListener(_pInterruptMoveEventListener);
    EventDispatcher::getInstance()->removeEventListener(_pChangeStateEventListener);
}

MovementComponent* MovementComponent::create(Point acceleration, Point gravity, float lowGravityFactor, float highGravityFactor) {
    MovementComponent* pMovementComponent = new MovementComponent();
	if (pMovementComponent != nullptr && pMovementComponent->init()) {
		pMovementComponent->autorelease();
		pMovementComponent->setAcceleration(acceleration);
		pMovementComponent->setGravity(gravity);
		pMovementComponent->setBasicGravity(gravity);
		pMovementComponent->_highGravityFactor = highGravityFactor;
		pMovementComponent->_lowGravityFactor = lowGravityFactor;


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
	_pChangeStateEventListener = EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(MovementComponent::onChangeState, this));

	// Add listeners to dispacadr
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEditMoveEventListener, 1);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pJumpEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pInterruptMoveEventListener, 1);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeStateEventListener, 1);
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
			//_direction.y = editMoveEvent->getDirection().y;
		}
		_bStartMoving = editMoveEvent->isStartMoving();

	}
}

void MovementComponent::onJump(EventCustom* pEvent) {
	events::JumpEvent* jumpEvent = static_cast<events::JumpEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(jumpEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	Point direction = jumpEvent->getDirection();
	if (componentOwner == eventSource) {
		if (jumpEvent->isStartJumping() && _eMovingState == core::ActorState::ON_FLOOR_STATE) {
			_speed.x = MAX_JUMP_SPEED*direction.x;
            _speed.y = MAX_JUMP_SPEED*direction.y;
			_eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
			sounds::HeroSoundComponent* pHeroSoundComp = static_cast<sounds::HeroSoundComponent*>(_owner->getComponent(sounds::HeroSoundComponent::COMPONENT_TYPE));
			if (pHeroSoundComp != nullptr ) {
				pHeroSoundComp->onJump(pEvent);
			}
			graphics::HeroAnimatedSpriteComponent* pHeroAnimComp = static_cast<graphics::HeroAnimatedSpriteComponent*>(_owner->getComponent(graphics::HeroAnimatedSpriteComponent::COMPONENT_TYPE));
			if (pHeroAnimComp != nullptr ) {
				pHeroAnimComp->onJump(pEvent);
			}
			events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
			EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
        } else {
            if (_speed.y > MIN_JUMP_SPEED) {
                _speed.y = MIN_JUMP_SPEED;
            }
        }
	}
}

void MovementComponent::onInterruptMove(EventCustom* pEvent) {
	events::InterruptMoveEvent* interruptMoveEvent = static_cast<events::InterruptMoveEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(interruptMoveEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		if (interruptMoveEvent->getStopX()) {
            _speed.x = 0.f;
        }
        if (interruptMoveEvent->getStopY()) {
            _speed.y = 0.f;
        }
	}
}

void MovementComponent::onChangeState(EventCustom* pEvent) {
	events::ChangeStateEvent* pChangeStateEvent = static_cast<events::ChangeStateEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(pChangeStateEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		if(pChangeStateEvent->getNewState() == core::ActorState::NOT_ON_FLOOR_STATE) {
			_eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
		} else {
			_eMovingState = core::ActorState::ON_FLOOR_STATE;
		}
	}
}

void MovementComponent::update(float fDt) {
	// compute next speed
	_speed = _speed + Point(_direction.x * _acceleration.x, _direction.y * _acceleration.y) + _gravity;

	/*if ( !(_direction.x < 0.1f && _direction.x > -0.1f) && (_direction.y < 0.1f && _direction.y > -0.1f)){
		CCLOG("HABBA");
		_speed.y = 0;
	}
	if ( !(_direction.y < 0.1f && _direction.y > -0.1f) && (_direction.x < 0.1f && _direction.x > -0.1f)){
		CCLOG("BLA BLA");
		_speed.x = 0;
	}*/

	if (!_bStartMoving){
		if(_speed.x > 0){
			_speed.x -= _acceleration.x;
		} else if (_speed.x < 0){
			_speed.x += _acceleration.x;
		}

		/*if(_speed.y > 0){
			_speed.y -= _acceleration.y;
		} else if (_speed.y < 0){
			_speed.y += _acceleration.y;
		}*/
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
    _previousPosition = pGeometryComponent->getPosition();
    //CCLOG("MovementComponent::update PREVIOUS POSITION %.2f, %.2f", _previousPosition.x, _previousPosition.y);
	Point nextPosition = pGeometryComponent->getPosition() + _speed * ENGINE_SPEED;

    _bIsLateralMoving = !(abs(nextPosition.x - _previousNextPositionComputed.x) < 1.f);

    _previousNextPositionComputed = nextPosition;

    physics::CollisionComponent* pCollisionComponent = static_cast<physics::CollisionComponent*>(_owner->getComponent(physics::CollisionComponent::COMPONENT_TYPE));
    if (pCollisionComponent == nullptr) {
        events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, nextPosition);
        EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
    } else {
        events::TestCollisionEvent* pTestCollisionEvent = new events::TestCollisionEvent(_owner, pGeometryComponent->getPosition(), nextPosition, pGeometryComponent->getSize());
        EventDispatcher::getInstance()->dispatchEvent(pTestCollisionEvent);
    }
}


}  // namespace physics
