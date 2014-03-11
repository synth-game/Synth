/*!
 * \file CollisionComponent.cpp
 * \brief Allow and compute collisions
 * \author Jijidici
 * \date 20/02/2014
 */
#include <cmath>
#include "CollisionComponent.h"
#include "core/SynthActor.h"
#include "events/ChangePositionEvent.h"
#include "events/ChangeStateEvent.h"
#include "events/InterruptMoveEvent.h"
#include "events/CollisionEvent.h"

#define SLOPE_THRESHOLD 3.f

namespace physics {

const char* CollisionComponent::COMPONENT_TYPE = "CollisionComponent";

CollisionComponent::CollisionComponent() 
	: SynthComponent()
	, _pPhysicCollision(nullptr)
	, _pLightCollision(nullptr)
	, _eMovingState(core::ActorState::JUMPING_STATE)
	, _pTestCollisionEventListener(nullptr)
	, _pChangeStateCollision(nullptr) {
}

CollisionComponent::~CollisionComponent() {
	if (_pPhysicCollision != nullptr) { delete _pPhysicCollision; }
	if (_pLightCollision != nullptr) { delete _pLightCollision; }
}

CollisionComponent* CollisionComponent::create() {
	CollisionComponent* pCollisionComponent = new CollisionComponent();
	if (pCollisionComponent != nullptr && pCollisionComponent->init()) {
		pCollisionComponent->autorelease();
	} else {
		CC_SAFE_DELETE(pCollisionComponent);
	}
	return pCollisionComponent;
}

void CollisionComponent::onTestCollision(EventCustom* pEvent) {
	events::TestCollisionEvent* pTestColEvent = static_cast<events::TestCollisionEvent*>(pEvent);
	core::SynthActor* pOwner = static_cast<core::SynthActor*>(_owner);
	core::SynthActor* pEventSource = static_cast<core::SynthActor*>(pTestColEvent->getSource());
	if (pOwner->getActorID() == pEventSource->getActorID()) {
		// initialize the computing position
		Point computingPos = pTestColEvent->getTargetPosition();

		// check if the component have a PhysicCollision
		if (_pPhysicCollision != nullptr) {
			ECollisionType eCollision = NO_COLLISION;
			if (_eMovingState == core::ActorState::ON_FLOOR_STATE) {
				eCollision = slopeTest(pTestColEvent, computingPos);
			} else {
				eCollision = boundingTest(pTestColEvent, computingPos);
			}

			events::InterruptMoveEvent* pInterruptMovementEvent = nullptr;
			if (eCollision == VERTICAL) {
				pInterruptMovementEvent = new events::InterruptMoveEvent(_owner, false, true, true);
				EventDispatcher::getInstance()->dispatchEvent(pInterruptMovementEvent);
			} else if (eCollision == HORIZONTAL) {
				pInterruptMovementEvent = new events::InterruptMoveEvent(_owner, true, false, true);
				EventDispatcher::getInstance()->dispatchEvent(pInterruptMovementEvent);

				// send CollisionEvent for sound and graphic components
				events::CollisionEvent* pCollisionEvent = new events::CollisionEvent(_owner);
				EventDispatcher::getInstance()->dispatchEvent(pCollisionEvent);
			}
		}

		//check if the component have a LightCollision
		if (_pLightCollision != nullptr) {
			Color4B aL = _pLightCollision->getCurrentColor(computingPos);
			CCLOG("> HERO COLOR : %d | %d | %d | %d", aL.r, aL.g, aL.b, aL.a);	
		}

		// Change position 
		events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, computingPos);
		EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
	}
}

void CollisionComponent::onChangeState(EventCustom* pEvent) {
	events::ChangeStateEvent* pChangeStateEvent = static_cast<events::ChangeStateEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(pChangeStateEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		if(pChangeStateEvent->getNewState() == core::ActorState::JUMPING_STATE) {
			_eMovingState = core::ActorState::JUMPING_STATE;
		}
	}
}

bool CollisionComponent::init() {
	SynthComponent::init(CollisionComponent::COMPONENT_TYPE);
	return true;
}

void CollisionComponent::initListeners() {
	// Listeners initialization
	_pTestCollisionEventListener = EventListenerCustom::create(events::TestCollisionEvent::EVENT_NAME, CC_CALLBACK_1(CollisionComponent::onTestCollision, this));
	_pChangeStateCollision = EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(CollisionComponent::onChangeState, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pTestCollisionEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeStateCollision, 1);
}

CollisionComponent::ECollisionType CollisionComponent::boundingTest(events::TestCollisionEvent* pInitiatorEvent, Point& resPosition) {
	ECollisionType eRet = NO_COLLISION;

	// build position-target vector
	Point currentPosition = Point(floor(pInitiatorEvent->getCurrentPosition().x), floor(pInitiatorEvent->getCurrentPosition().y));
	Point targetPosition = Point(floor(pInitiatorEvent->getTargetPosition().x), floor(pInitiatorEvent->getTargetPosition().y));
	Point movementDir = targetPosition - currentPosition;
	float movementLength = movementDir.getLength();
	Point movementStep = movementDir.normalize();
	Size halfSize = pInitiatorEvent->getSize()/2;
	Size thirdSize = pInitiatorEvent->getSize()/3;
			
	Point centerPos = currentPosition;
	core::ActorState nextState = core::ActorState::JUMPING_STATE;

	// test pixel by pixel the center point movement - stop if collide
	while((centerPos-currentPosition).getLength() < movementLength) {
		Point nextCenterPos = centerPos + movementStep;
		//corner points
		Point blPos = Point(nextCenterPos.x-halfSize.width, nextCenterPos.y-halfSize.height);
		Point brPos = Point(nextCenterPos.x+halfSize.width, nextCenterPos.y-halfSize.height);
		Point trPos = Point(nextCenterPos.x+halfSize.width, nextCenterPos.y+halfSize.height);
		Point tlPos = Point(nextCenterPos.x-halfSize.width, nextCenterPos.y+halfSize.height);

		//intermediar lateral point
		Point l1Pos = Point(nextCenterPos.x-halfSize.width, nextCenterPos.y-halfSize.height+thirdSize.height);
		Point l2Pos = Point(nextCenterPos.x-halfSize.width, nextCenterPos.y-halfSize.height+2*thirdSize.height);
		Point r1Pos = Point(nextCenterPos.x+halfSize.width, nextCenterPos.y-halfSize.height+thirdSize.height);
		Point r2Pos = Point(nextCenterPos.x+halfSize.width, nextCenterPos.y-halfSize.height+2*thirdSize.height);
		Point tPos = Point(nextCenterPos.x, nextCenterPos.y+halfSize.height);

		// case of hypothetical landing
		if (_pPhysicCollision->collide(blPos) || _pPhysicCollision->collide(brPos)) { 
			Point savedCenterPos = centerPos;
			//test if bottom-center point collide the ground
			while((savedCenterPos-currentPosition).getLength() < movementLength) {
				Point nextSavedCenterPos = savedCenterPos + movementStep;
				Point bcPos = Point(nextSavedCenterPos.x, nextSavedCenterPos.y-halfSize.height);

				if (_pPhysicCollision->collide(bcPos)) {
					eRet = VERTICAL;
					nextState = core::ActorState::ON_FLOOR_STATE;
					break;
				}
				savedCenterPos = nextSavedCenterPos;
			}

			centerPos = savedCenterPos;
			break;
		} else if (_pPhysicCollision->collide(trPos)
			   || _pPhysicCollision->collide(tlPos)
			   || _pPhysicCollision->collide(l1Pos)
			   || _pPhysicCollision->collide(l2Pos)
			   || _pPhysicCollision->collide(r1Pos)
			   || _pPhysicCollision->collide(r2Pos)) {
			eRet = HORIZONTAL;
			break;
		} else if (_pPhysicCollision->collide(tPos)) {
			eRet = VERTICAL;
			break;
		}
		
		centerPos = nextCenterPos;
	}

	//update position
	resPosition = centerPos;

	//update state of Collision and Movement components
	if(nextState != _eMovingState) {
		_eMovingState = nextState;
		events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, nextState);
		EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
	}

	return eRet;
}

CollisionComponent::ECollisionType CollisionComponent::slopeTest(events::TestCollisionEvent* pInitiatorEvent, Point& resPosition) {
	ECollisionType eRet = VERTICAL;

	Size halfSize = pInitiatorEvent->getSize()/2;
	Size thirdSize = pInitiatorEvent->getSize()/3;
	Point currentPosition = Point(floor(pInitiatorEvent->getCurrentPosition().x), floor(pInitiatorEvent->getCurrentPosition().y));
	Point targetPosition = Point(floor(pInitiatorEvent->getTargetPosition().x), floor(pInitiatorEvent->getTargetPosition().y));
	Point currentBCPosition = Point(currentPosition.x, currentPosition.y-halfSize.height);
	Point targetBCPosition = Point(targetPosition.x, targetPosition.y-halfSize.height);

	// Slope movement - only if you have a lateral movement
	if (currentPosition.x != targetPosition.x) {
		//compute targetPosition on the floor
		if (_pPhysicCollision->collide(targetBCPosition)) { // increasing slope
			targetBCPosition = _pPhysicCollision->getNextVoidPixel(targetBCPosition, PhysicCollision::TOP);
		} else { //decreasing slope
			targetBCPosition = _pPhysicCollision->getNextWallPixel(targetBCPosition, PhysicCollision::BOTTOM);
			targetBCPosition.y += 1.f;
		}

		//compute slope coef to move through the slopes
		float slopeCoef = 0.f;
		if (targetBCPosition.x > currentBCPosition.x) {
			slopeCoef = (targetBCPosition.y-currentBCPosition.y)/(targetBCPosition.x-currentBCPosition.x);
		} else {
			slopeCoef = (targetBCPosition.y-currentBCPosition.y)/(currentBCPosition.x-targetBCPosition.x);
		}

		if (slopeCoef > SLOPE_THRESHOLD) {
			//too big slope - stop it
			targetPosition = currentPosition;
			eRet = HORIZONTAL;
		} else if (slopeCoef < -SLOPE_THRESHOLD) {
			//too big hole - test if the bottom-left and bottom-right point also fall - unefficient sleeping code
			Point targetBLPosition = Point(targetPosition.x-halfSize.width, targetPosition.y-halfSize.height);
			Point targetBRPosition = Point(targetPosition.x+halfSize.width, targetPosition.y-halfSize.height);
			if (_pPhysicCollision->collide(targetBLPosition) || _pPhysicCollision->collide(targetBRPosition)) {
				targetPosition.y = (targetPosition.y + currentPosition.y)/2.f;
			} else {
				_eMovingState = core::ActorState::JUMPING_STATE;
				events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
				EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
			}
		} else {
			targetPosition = targetBCPosition + Point(0.f, halfSize.height);
		}
	} else {
		// manage passive gravity effect
		targetPosition = currentPosition;
	}

	// Bounding test on the 6 others bounding points
	targetPosition = Point(floor(targetPosition.x), floor (targetPosition.y));
	Point movementDir = targetPosition - currentPosition;
	float movementLength = movementDir.getLength();
	Point movementStep = movementDir.normalize();
	Point centerPos = currentPosition;

	// test pixel by pixel the center point movement - stop if collide
	while((centerPos-currentPosition).getLength() < movementLength) {
		Point nextCenterPos = centerPos + movementStep;
		//corner points
		Point trPos = Point(nextCenterPos.x+halfSize.width, nextCenterPos.y+halfSize.height);
		Point tlPos = Point(nextCenterPos.x-halfSize.width, nextCenterPos.y+halfSize.height);

		//intermediar lateral point
		Point l1Pos = Point(nextCenterPos.x-halfSize.width, nextCenterPos.y-halfSize.height+thirdSize.height);
		Point l2Pos = Point(nextCenterPos.x-halfSize.width, nextCenterPos.y-halfSize.height+2*thirdSize.height);
		Point r1Pos = Point(nextCenterPos.x+halfSize.width, nextCenterPos.y-halfSize.height+thirdSize.height);
		Point r2Pos = Point(nextCenterPos.x+halfSize.width, nextCenterPos.y-halfSize.height+2*thirdSize.height);

		if(_pPhysicCollision->collide(trPos)
		|| _pPhysicCollision->collide(tlPos)
		|| _pPhysicCollision->collide(l1Pos)
		|| _pPhysicCollision->collide(l2Pos)
		|| _pPhysicCollision->collide(r1Pos)
		|| _pPhysicCollision->collide(r2Pos)) {
			eRet = HORIZONTAL;
			break;
		}
		centerPos = nextCenterPos;
	}
	
	resPosition = centerPos;
	return eRet;
}

}  // namespace physics
