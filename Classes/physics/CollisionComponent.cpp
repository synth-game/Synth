/*!
 * \file CollisionComponent.cpp
 * \brief Allow and compute collisions
 * \author Jijidici
 * \date 20/02/2014
 */
#include <cmath>
#include <string>
#include <vector>
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
	EventDispatcher::getInstance()->removeEventListener(_pTestCollisionEventListener);
	EventDispatcher::getInstance()->removeEventListener(_pChangeStateCollision);
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
		if (_pPhysicCollision != nullptr && _pLightCollision != nullptr) {
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
	core::ActorState nextState = core::ActorState::JUMPING_STATE;

	// build position-target vector
	Point currentPosition = Point(pInitiatorEvent->getCurrentPosition().x, pInitiatorEvent->getCurrentPosition().y);
	Point targetPosition = Point(pInitiatorEvent->getTargetPosition().x, pInitiatorEvent->getTargetPosition().y);
	Point movementDir = targetPosition - currentPosition;
	float fMovementLength = movementDir.getLength();
	Point movementStep = movementDir.normalize();
	Size halfSize = pInitiatorEvent->getSize()/2.f;
	Size quarterSize = pInitiatorEvent->getSize()/4.f;
	float fStepCountToExecute = 100000.f; // default big value to initialize
	
	Point centerPos = currentPosition;
	// corner points
	Point blPos = Point(centerPos.x-halfSize.width, centerPos.y-halfSize.height);
	Point brPos = Point(centerPos.x+halfSize.width, centerPos.y-halfSize.height);
	Point trPos = Point(centerPos.x+halfSize.width, centerPos.y+halfSize.height);
	Point tlPos = Point(centerPos.x-halfSize.width, centerPos.y+halfSize.height);

	// middle points
	Point bcPos = Point(centerPos.x, centerPos.y-halfSize.height);
	Point lcPos = Point(centerPos.x-halfSize.width, centerPos.y);
	Point tcPos = Point(centerPos.x, centerPos.y+halfSize.height);
	Point rcPos = Point(centerPos.x+halfSize.width, centerPos.y);

	// quarter laeral points
	Point l1Pos = Point(centerPos.x-halfSize.width, centerPos.y-quarterSize.height);
	Point l2Pos = Point(centerPos.x-halfSize.width, centerPos.y+quarterSize.height);
	Point r1Pos = Point(centerPos.x+halfSize.width, centerPos.y-quarterSize.height);
	Point r2Pos = Point(centerPos.x+halfSize.width, centerPos.y+quarterSize.height);

	// first, test if the actor land on the ground
	float fBCSampleCount = countStepToNextPixel(bcPos, movementStep, false, fMovementLength);
	if ((!_pPhysicCollision->collide(bcPos) || _pLightCollision->isInWhiteLight(bcPos)) && fBCSampleCount != -1.f) {
		// bottom center point collide a wall
		fStepCountToExecute = fBCSampleCount;
		eRet = VERTICAL;
		nextState = core::ActorState::ON_FLOOR_STATE;
	} else {
		// test other point
		std::vector<Point> pointToTest;
		if (!_pPhysicCollision->collide(blPos) || _pLightCollision->isInWhiteLight(blPos)) { pointToTest.push_back(blPos); }
		if (!_pPhysicCollision->collide(brPos) || _pLightCollision->isInWhiteLight(brPos)) { pointToTest.push_back(brPos); }
		if (!_pPhysicCollision->collide(trPos) || _pLightCollision->isInWhiteLight(trPos)) { pointToTest.push_back(trPos); }
		if (!_pPhysicCollision->collide(tlPos) || _pLightCollision->isInWhiteLight(tlPos)) { pointToTest.push_back(tlPos); }
		if (!_pPhysicCollision->collide(lcPos) || _pLightCollision->isInWhiteLight(lcPos)) { pointToTest.push_back(lcPos); }
		if (!_pPhysicCollision->collide(tcPos) || _pLightCollision->isInWhiteLight(tcPos)) { pointToTest.push_back(tcPos); }
		if (!_pPhysicCollision->collide(rcPos) || _pLightCollision->isInWhiteLight(rcPos)) { pointToTest.push_back(rcPos); }
		if (!_pPhysicCollision->collide(l1Pos) || _pLightCollision->isInWhiteLight(l1Pos)) { pointToTest.push_back(l1Pos); }
		if (!_pPhysicCollision->collide(l2Pos) || _pLightCollision->isInWhiteLight(l2Pos)) { pointToTest.push_back(l2Pos); }
		if (!_pPhysicCollision->collide(r1Pos) || _pLightCollision->isInWhiteLight(r1Pos)) { pointToTest.push_back(r1Pos); }
		if (!_pPhysicCollision->collide(r2Pos) || _pLightCollision->isInWhiteLight(r2Pos)) { pointToTest.push_back(r2Pos); }

		std::vector<float> stepsVector;
		for (std::vector<Point>::iterator itPoint=pointToTest.begin(); itPoint!=pointToTest.end(); ++itPoint) {
			float fPossibleStepCount = countStepToNextPixel(*itPoint, movementStep, false, fMovementLength);
			stepsVector.push_back(fPossibleStepCount);
		}

		for (std::vector<float>::iterator itStep=stepsVector.begin(); itStep!=stepsVector.end(); ++itStep) {
			if (*itStep < fStepCountToExecute && *itStep >= 0) {
				fStepCountToExecute = *itStep;
			}
		}

		// if step count is again the default value, there is no collision => set the max movement length
		if (fStepCountToExecute == 100000.f) { fStepCountToExecute = fMovementLength; }
	}

	//update position
	resPosition = centerPos + (movementStep*fStepCountToExecute);

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
		if (_pPhysicCollision->collide(targetBCPosition) && !_pLightCollision->isInWhiteLight(targetBCPosition)) { // increasing slope
			targetBCPosition = getNextPixel(targetBCPosition, Point(0.f, 1.f), true);
		} else { //decreasing slope
			targetBCPosition = getNextPixel(targetBCPosition, Point(0.f, -1.f), false);
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
			if ((_pPhysicCollision->collide(targetBLPosition) && !_pLightCollision->isInWhiteLight(targetBLPosition))
			|| (_pPhysicCollision->collide(targetBRPosition) && !_pLightCollision->isInWhiteLight(targetBRPosition))) {
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

		if((_pPhysicCollision->collide(trPos) && !_pLightCollision->isInWhiteLight(trPos))
		|| (_pPhysicCollision->collide(tlPos) && !_pLightCollision->isInWhiteLight(tlPos))
		|| (_pPhysicCollision->collide(l1Pos) && !_pLightCollision->isInWhiteLight(l1Pos))
		|| (_pPhysicCollision->collide(l2Pos) && !_pLightCollision->isInWhiteLight(l2Pos))
		|| (_pPhysicCollision->collide(r1Pos) && !_pLightCollision->isInWhiteLight(r1Pos))
		|| (_pPhysicCollision->collide(r2Pos) && !_pLightCollision->isInWhiteLight(r2Pos))) {
			eRet = HORIZONTAL;
			break;
		}
		centerPos = nextCenterPos;
	}
	
	resPosition = centerPos;
	return eRet;
}

Point CollisionComponent::getNextPixel(Point position, Point direction, bool bVoid) {
	Point wantedPixel = position;

	bool bSampleState = !_pPhysicCollision->collide(wantedPixel) || _pLightCollision->isInWhiteLight(wantedPixel);
	while(bSampleState != bVoid) {
		wantedPixel = wantedPixel + direction;

		// out of image
		if(wantedPixel.x < 0 || wantedPixel.x >= _pPhysicCollision->getZoneWidth() || wantedPixel.y < 0 || wantedPixel.y >= _pPhysicCollision->getZoneHeight()) {
			wantedPixel = position;
			break;
		}

		bSampleState = !_pPhysicCollision->collide(wantedPixel) || _pLightCollision->isInWhiteLight(wantedPixel);
	}

	return wantedPixel;
}

float CollisionComponent::countStepToNextPixel(Point position, Point direction, bool bVoid, float fMaxLength) {
	float fRet = 0.f;
	Point wantedPixel = position + direction;

	bool bSampleState = !_pPhysicCollision->collide(wantedPixel) || _pLightCollision->isInWhiteLight(wantedPixel);
	while(bSampleState != bVoid && fRet < fMaxLength) {
		wantedPixel = wantedPixel + direction;

		// out of image
		if(wantedPixel.x < 0 || wantedPixel.x >= _pPhysicCollision->getZoneWidth() || wantedPixel.y < 0 || wantedPixel.y >= _pPhysicCollision->getZoneHeight()) {
			fRet = 0.f;
			break;
		}

		bSampleState = !_pPhysicCollision->collide(wantedPixel) || _pLightCollision->isInWhiteLight(wantedPixel);
		++fRet;
	}

	if (fRet >= fMaxLength) {
		fRet = -1.f;
	}

	return fRet;
}

}  // namespace physics
