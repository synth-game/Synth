#include "StickMovementComponent.h"
#include "CollisionComponent.h"
#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "events/InterruptMoveEvent.h"
#include "events/ChangePositionEvent.h"
#include "events/CollisionEvent.h"
#include "events/TestCollisionEvent.h"
#include "events/ChangeStateEvent.h"
#include "events/ChangePositionEvent.h"
#include "events/TestCollisionEvent.h"
#include "sounds/HeroSoundComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"

#define MAX_X_SPEED 200.f
#define MAX_Y_SPEED 400.f
#define MAX_JUMP_SPEED 400.f
#define MIN_JUMP_SPEED 100.f
#define ENGINE_SPEED 0.015

namespace physics
{

StickMovementComponent::StickMovementComponent()
	: MovementComponent(),
	_eCurrentDirection(BOTTOM),
	_bIsSticked(false),
	_bIsJumping(false) {
}

StickMovementComponent::~StickMovementComponent() {
	//EventDispatcher::getInstance()->removeEventListener(_pChangeTargetEventListener);
}

bool StickMovementComponent::init() {
	SynthComponent::init(MovementComponent::COMPONENT_TYPE);
	return true;
}
    
void StickMovementComponent::onEnter() {
    physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
    CCASSERT(pGeometryComponent != nullptr, "MovementComponent needs a GeometryComponent added to its owner");
    Point currentPosition = pGeometryComponent->getPosition();
    _previousPosition = currentPosition;
}
    
void StickMovementComponent::initListeners() {
    // Listeners initialization
	_pEditMoveEventListener = EventListenerCustom::create(events::EditMoveEvent::EVENT_NAME, CC_CALLBACK_1(StickMovementComponent::onEditMove, this));
	_pJumpEventListener = EventListenerCustom::create(events::JumpEvent::EVENT_NAME, CC_CALLBACK_1(StickMovementComponent::onJump, this));
	_pInterruptMoveEventListener = EventListenerCustom::create(events::InterruptMoveEvent::EVENT_NAME, CC_CALLBACK_1(StickMovementComponent::onInterruptMove, this));
	_pChangeStateEventListener = EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(StickMovementComponent::onChangeState, this));
    
	// Add listeners to dispacadr
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEditMoveEventListener, 1);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pJumpEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pInterruptMoveEventListener, 1);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeStateEventListener, 1);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(EventListenerCustom::create(events::CollisionEvent::EVENT_NAME, CC_CALLBACK_1(StickMovementComponent::onCollisionEvent, this)), 1);
}

StickMovementComponent* StickMovementComponent::create(Point acceleration, Point gravity) {
	StickMovementComponent* pStickMovementComponent = new StickMovementComponent();
	if (pStickMovementComponent != nullptr && pStickMovementComponent->init()) {
		pStickMovementComponent->autorelease();
		pStickMovementComponent->setAcceleration(acceleration);
        pStickMovementComponent->setGravity(gravity);
        pStickMovementComponent->setBasicGravity(gravity);
	} else {
		CC_SAFE_DELETE(pStickMovementComponent);
	}
	return pStickMovementComponent;
}
    
void StickMovementComponent::onEditMove(EventCustom* pEvent) {
	events::EditMoveEvent* editMoveEvent = static_cast<events::EditMoveEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(editMoveEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
        CCLOG("StickMovementComponent::onEditMove DIRECTION = %.2f, %.2f", editMoveEvent->getDirection().x, editMoveEvent->getDirection().y);
		if (editMoveEvent->getChangeX()) {
			_direction.x = editMoveEvent->getDirection().x;
            if (_direction.x == -1) {
                CCLOG("StickMovementComponent::onEditMove MOVING LEFT");
                _eCurrentDirection = LEFT;
            }
            else if (_direction.x == 1) {
                CCLOG("StickMovementComponent::onEditMove MOVING RIGHT");
                _eCurrentDirection = RIGHT;
            }
		}
		if (editMoveEvent->getChangeY()) {
			_direction.y = editMoveEvent->getDirection().y;
            if (_direction.y == -1) {
                CCLOG("StickMovementComponent::onEditMove MOVING TOP");
                _eCurrentDirection = TOP;
            }
            else if (_direction.y == 1) {
                CCLOG("StickMovementComponent::onEditMove MOVING BOTTOM");
                _eCurrentDirection = BOTTOM;
            }
		}
		_bStartMoving = editMoveEvent->isStartMoving();

	}
}

void StickMovementComponent::onCollisionEvent(EventCustom* pEvent) {
    events::CollisionEvent* pCollisionEvent = static_cast<events::CollisionEvent*>(pEvent);
    core::SynthActor* eventSource = static_cast<core::SynthActor*>(pCollisionEvent->getSource());
    core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
    if (componentOwner == eventSource) {
        _bIsJumping = false;
        physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
        CCASSERT(pGeometryComponent != nullptr, "MovementComponent needs a GeometryComponent added to its owner");
        Point currentPosition = pGeometryComponent->getPosition();
        Point direction = Point(currentPosition.x - _previousNextPositionComputed.x, currentPosition.y - _previousNextPositionComputed.y);
        //CCLOG("StickMovementComponent::onCollisionEvent DIRECTION = %.2f, %.2f", direction.x, direction.y);
        switch (_eCurrentDirection) {
            case BOTTOM:
                CCLOG("StickMovementComponent::onCollisionEvent COLLISION BOTTOM");
                _eMovingState = core::ActorState::STUCK_BOTTOM_STATE;
                break;
            case LEFT:
                CCLOG("StickMovementComponent::onCollisionEvent COLLISION LEFT");
                _eMovingState = core::ActorState::STUCK_LEFT_STATE;
                break;
            case RIGHT:
                CCLOG("StickMovementComponent::onCollisionEvent COLLISION RIGHT");
                _eMovingState = core::ActorState::STUCK_RIGHT_STATE;
                break;
            case TOP:
                CCLOG("StickMovementComponent::onCollisionEvent COLLISION TOP");
                _eMovingState = core::ActorState::STUCK_TOP_STATE;
                break;
        }
        /*if (direction.x > 0) {
            if (direction.y > 0 && direction.y > 2) {
                CCLOG("StickMovementComponent::onCollisionEvent MOVING LEFT BUT STICKED ON FLOOR");
                _eMovingState = core::ActorState::STUCK_BOTTOM_STATE;
            }
            else if (direction.y < 0 && direction.y < -2) {
                CCLOG("StickMovementComponent::onCollisionEvent MOVING LEFT BUT STICKED ON TOP");
                _eMovingState = core::ActorState::STUCK_TOP_STATE;
            }
            else {
                CCLOG("StickMovementComponent::onCollisionEvent STICKED ON LEFT WALL");
                _eMovingState = core::ActorState::STUCK_LEFT_STATE;
            }
        }
        else if (direction.x < 0) {
            if (direction.y > 0) {
                CCLOG("StickMovementComponent::onCollisionEvent MOVING RIGHT BUT STICKED ON FLOOR");
                _eMovingState = core::ActorState::STUCK_BOTTOM_STATE;
            }
            else if (direction.y < 0) {
                CCLOG("StickMovementComponent::onCollisionEvent MOVING RIGHT BUT STICKED ON TOP");
                _eMovingState = core::ActorState::STUCK_TOP_STATE;
            }
            else {
                CCLOG("StickMovementComponent::onCollisionEvent STICKED ON RIGHT WALL");
                _eMovingState = core::ActorState::STUCK_RIGHT_STATE;
            }
        }
        else {
            if (direction.y > 0) {
                CCLOG("StickMovementComponent::onCollisionEvent STICKED ON FLOOR");
                _eMovingState = core::ActorState::STUCK_BOTTOM_STATE;
            }
            else if (direction.y < 0) {
                CCLOG("StickMovementComponent::onCollisionEvent STICKED ON TOP");
                _eMovingState = core::ActorState::STUCK_TOP_STATE;
            }

        }*/
        events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
        EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
        _bIsSticked = true;
    }
}
    
void StickMovementComponent::onJump(EventCustom* pEvent) {
    events::JumpEvent* jumpEvent = static_cast<events::JumpEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(jumpEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	Point direction = jumpEvent->getDirection();
	if (componentOwner == eventSource) {
        if (jumpEvent->isStartJumping() && _eMovingState == core::ActorState::STUCK_TOP_STATE) {
            _bIsJumping = false;
            CCLOG("StickMovementComponent::onJump FALL");
            _eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
            events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
			EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
            if (_speed.y > MIN_JUMP_SPEED) {
                _speed.y = MIN_JUMP_SPEED;
            }
            return;
        }
		if ((jumpEvent->isStartJumping() && _eMovingState == core::ActorState::ON_FLOOR_STATE) || (jumpEvent->isStartJumping() && _bIsSticked)) {
            _bIsJumping = true;
            /* Offset on jump depending on the surface */
            //CCLOG("StickMovementComponent::onJump STATE = %d", _eMovingState);
            physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
            CCASSERT(pGeometryComponent != nullptr, "MovementComponent needs a GeometryComponent added to its owner");
            Point currentPos = pGeometryComponent->getPosition();
            if (_eMovingState == core::ActorState::STUCK_LEFT_STATE) {
                //CCLOG("StickMovementComponent::onJump TRYING TO JUMP WHEN STICKED ON BOTTOM");
                events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, Point(currentPos.x + 10, currentPos.y));
                EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
            }
            else if (_eMovingState == core::ActorState::STUCK_RIGHT_STATE) {
                //CCLOG("StickMovementComponent::onJump TRYING TO JUMP WHEN STICKED ON BOTTOM");
                events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, Point(currentPos.x - 10, currentPos.y));
                EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
            }
            
            
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

void StickMovementComponent::onChangeState(EventCustom* pEvent) {
    events::ChangeStateEvent* pChangeStateEvent = static_cast<events::ChangeStateEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(pChangeStateEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
        _eMovingState = pChangeStateEvent->getNewState();
        _bIsSticked = _eMovingState == (core::ActorState::STUCK_BOTTOM_STATE || _eMovingState == core::ActorState::STUCK_LEFT_STATE || _eMovingState == core::ActorState::STUCK_RIGHT_STATE || core::ActorState::STUCK_TOP_STATE);
	}
}

void StickMovementComponent::onInterruptMove(EventCustom* pEvent) {
    MovementComponent::onInterruptMove(pEvent);
}

    
void StickMovementComponent::update(float fDt)
{
    if (!_bIsSticked) {
        MovementComponent::update(fDt);
        physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
        CCASSERT(pGeometryComponent != nullptr, "MovementComponent needs a GeometryComponent added to its owner");
        Point currentPosition = pGeometryComponent->getPosition();
        
        //CCLOG("StickMovementComponent::update CURRENT POSITION %.2f,%.2f PREVIOUS POSITION %.2f, %.2f", currentPosition.x, currentPosition.y, _previousPosition.x, _previousPosition.y);

        /*if (currentPosition.x < _previousNextPositionComputed.x) {
            _eCurrentDirection = RIGHT;
            CCLOG("StickMovementComponent::update RIGHT");
        }
        if (currentPosition.x > _previousNextPositionComputed.x) {
            _eCurrentDirection = LEFT;
            CCLOG("StickMovementComponent::update LEFT");
        }*/
        if (!_bStartMoving) {
            if (currentPosition.y < _previousPosition.y) {
                _eCurrentDirection = BOTTOM;
            }
            if (currentPosition.y > _previousPosition.y) {
                _eCurrentDirection = TOP;
            }
        }
        switch (_eCurrentDirection) {
            case RIGHT:
                CCLOG("StickMovementComponent::update RIGHT");
                break;
            case LEFT:
                CCLOG("StickMovementComponent::update LEFT");
                break;
            case TOP:
                CCLOG("StickMovementComponent::update TOP");
                break;
            case BOTTOM:
                CCLOG("StickMovementComponent::update BOTTOM");
                break;
        }
    }
}
}  // namespace physics
