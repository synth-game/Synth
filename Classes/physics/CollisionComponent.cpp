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

#define SLOPE_THRESHOLD 1.5f

namespace physics {

const char* CollisionComponent::COMPONENT_TYPE = "CollisionComponent";

CollisionComponent::CollisionComponent()
	: SynthComponent()
	, _pPhysicCollision(nullptr)
	, _eMovingState(core::ActorState::NOT_ON_FLOOR_STATE)
	, _pTestCollisionEventListener(nullptr)
	, _pChangeStateCollision(nullptr) {
}

CollisionComponent::~CollisionComponent() {
	if (_pPhysicCollision != nullptr) { delete _pPhysicCollision; }
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
				delete pInterruptMovementEvent;
			} else if (eCollision == HORIZONTAL) {
				pInterruptMovementEvent = new events::InterruptMoveEvent(_owner, true, false, true);
				EventDispatcher::getInstance()->dispatchEvent(pInterruptMovementEvent);
				delete pInterruptMovementEvent;
			} else if (eCollision == BOTH) {
				pInterruptMovementEvent = new events::InterruptMoveEvent(_owner, true, true, true);
				EventDispatcher::getInstance()->dispatchEvent(pInterruptMovementEvent);
				delete pInterruptMovementEvent;
			}

			if (eCollision == HORIZONTAL || eCollision == BOTH) {
				// send CollisionEvent for sound and graphic components
				events::CollisionEvent* pCollisionEvent = new events::CollisionEvent(_owner);
				EventDispatcher::getInstance()->dispatchEvent(pCollisionEvent);
				delete pCollisionEvent;
			}
		}

		//check if the PhysicCollision have a LightCollision
		LightCollision* pLightCollision = _pPhysicCollision->getLightCollision();
		if (pLightCollision != nullptr) {
			Color4B aL = pLightCollision->getCurrentColor(computingPos);
		}

		// Change position
		if (!pTestColEvent->getCurrentPosition().equals(computingPos)) {
            //CCLOG("CollisionComponent::onTestCollision SEND CHANGE POSITION EVENT current pos %.2f, %.2f | computing pos %.2f %.2f", pTestColEvent->getCurrentPosition().x,pTestColEvent->getCurrentPosition().y, computingPos.x, computingPos.y);
            events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, computingPos);
            EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
			delete pChangePositionEvent;
        }

    }
}

void CollisionComponent::onChangeState(EventCustom* pEvent) {
	events::ChangeStateEvent* pChangeStateEvent = static_cast<events::ChangeStateEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(pChangeStateEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	if (componentOwner == eventSource) {
		if(pChangeStateEvent->getNewState() == core::ActorState::NOT_ON_FLOOR_STATE) {
			_eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
		}
	}
}

CollisionComponent::ECollisionType CollisionComponent::boundingTest(events::TestCollisionEvent* pInitiatorEvent, Point& resPosition) {
	ECollisionType eRet = NO_COLLISION;
	core::ActorState nextState = core::ActorState::NOT_ON_FLOOR_STATE;

	// build position-target vector
	Point currentPosition = Point(floor(pInitiatorEvent->getCurrentPosition().x), floor(pInitiatorEvent->getCurrentPosition().y));
	Point targetPosition = Point(floor(pInitiatorEvent->getTargetPosition().x), floor(pInitiatorEvent->getTargetPosition().y));
	Point movementDir = targetPosition - currentPosition;
	Size halfSize = pInitiatorEvent->getSize()/2.f;
	Size quarterSize = pInitiatorEvent->getSize()/4.f;
	float fMovementLength;
	float fBigMovementLength;
	Point movementStep;
	bool bIsOnGround = false;

	Point centerPos = currentPosition;

	// Test horizontal, then vertical displacement
	for (int i=0; i<2; ++i) {
		if (i==0) {
			// first loop - horizontal displacement
			fMovementLength = abs(movementDir.x);
			fBigMovementLength = pInitiatorEvent->getSize().width;
			movementStep = Point(movementDir.x, 0).normalize();
		} else {
			// second loop - vertical displacement
			fMovementLength = abs(movementDir.y);
			fBigMovementLength = pInitiatorEvent->getSize().height;
			movementStep = Point(0, movementDir.y).normalize();
		}

		float fStepCountToExecute = 100000.f; // default big value to initialize

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
		float fBCSampleCount = _pPhysicCollision->countStepToNextPixel(bcPos, movementStep, false, fMovementLength);
		float fBigBCSampleCount = _pPhysicCollision->countStepToNextPixel(bcPos, movementStep, false, fBigMovementLength);
		float fBLSampleCount = _pPhysicCollision->countStepToNextPixel(blPos, movementStep, false, fMovementLength);
		float fBRSampleCount = _pPhysicCollision->countStepToNextPixel(brPos, movementStep, false, fMovementLength);
		if ((!_pPhysicCollision->collide(bcPos)) && fBCSampleCount >= 0.f // bottom center point collide a wall
			&& _pPhysicCollision->collide(bcPos + movementStep*fBCSampleCount + Point(0., -1)) ) { // test if there is void below the moved bc pixel
			fStepCountToExecute = fBCSampleCount;
			bIsOnGround = true;
		} else {
			std::vector<Point> pointToTest;

			// test bottom point first, if ONLY one of them collide, stick the actor on the ground (XOR operator)
			if ((!_pPhysicCollision->collide(blPos) && fBLSampleCount >= 0.f) != (!_pPhysicCollision->collide(brPos) && fBRSampleCount >= 0.f)
				&& _pPhysicCollision->collide(bcPos + movementStep*fBigBCSampleCount + Point(0., -1))) { // test if there is void below the moved bc pixel) {
					fStepCountToExecute = std::min(fBigBCSampleCount, fMovementLength);
					bIsOnGround = true;
			} else {

				// test other point
				if (!_pPhysicCollision->collide(blPos)) { pointToTest.push_back(blPos); }
				if (!_pPhysicCollision->collide(brPos)) { pointToTest.push_back(brPos); }
				if (!_pPhysicCollision->collide(trPos)) { pointToTest.push_back(trPos); }
				if (!_pPhysicCollision->collide(tlPos)) { pointToTest.push_back(tlPos); }
				if (!_pPhysicCollision->collide(lcPos)) { pointToTest.push_back(lcPos); }
				if (!_pPhysicCollision->collide(tcPos)) { pointToTest.push_back(tcPos); }
				if (!_pPhysicCollision->collide(rcPos)) { pointToTest.push_back(rcPos); }
				if (!_pPhysicCollision->collide(l1Pos)) { pointToTest.push_back(l1Pos); }
				if (!_pPhysicCollision->collide(l2Pos)) { pointToTest.push_back(l2Pos); }
				if (!_pPhysicCollision->collide(r1Pos)) { pointToTest.push_back(r1Pos); }
				if (!_pPhysicCollision->collide(r2Pos)) { pointToTest.push_back(r2Pos); }

				std::vector<float> stepsVector;
				for (std::vector<Point>::iterator itPoint=pointToTest.begin(); itPoint!=pointToTest.end(); ++itPoint) {
					float fPossibleStepCount = _pPhysicCollision->countStepToNextPixel(*itPoint, movementStep, false, fMovementLength);
					stepsVector.push_back(fPossibleStepCount);
				}

				for (std::vector<float>::iterator itStep=stepsVector.begin(); itStep!=stepsVector.end(); ++itStep) {
					if (*itStep < fStepCountToExecute && *itStep >= 0) {
						fStepCountToExecute = *itStep;
					}
				}
			}

			// if step count is again the default value, there is no collision => set the max movement length
			if (fStepCountToExecute == 100000.f) {
				fStepCountToExecute = fMovementLength; 
			} else {
				if (i==0) {
					eRet = HORIZONTAL;
				} else {
					if (eRet == HORIZONTAL) {
						eRet = BOTH;
					} else {
						eRet = VERTICAL;
					}
					
				}
			}
		}

		centerPos = centerPos + (movementStep*fStepCountToExecute);

		if(bIsOnGround) { // in this case, we break. Either we've already done the 2 loops, or the actor land on the ground and we don't compute vertical displacement
			if (eRet == HORIZONTAL) {
				eRet = BOTH;
			} else {
				eRet = VERTICAL;
			}
			nextState = core::ActorState::ON_FLOOR_STATE;
			break;
		}
	}

	//update position
	resPosition = centerPos;

	//update state of Collision and Movement components
	if(nextState != _eMovingState) {
		_eMovingState = nextState;
        events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
        EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
		delete pChangeStateEvent;
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
			targetBCPosition = _pPhysicCollision->getNextPixel(targetBCPosition, Point(0.f, 1.f), true);
		} else { //decreasing slope
			targetBCPosition = _pPhysicCollision->getNextPixel(targetBCPosition, Point(0.f, -1.f), false);
			targetBCPosition.y += 1.f;
		}

		// case where actor is out of the image
		if (targetBCPosition.x<0.f || targetBCPosition.y<0.f) {
			_eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
            events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
            EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
			delete pChangeStateEvent;
		} else {
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
				eRet = BOTH;
			} else if (slopeCoef < -SLOPE_THRESHOLD) {
				//too big hole - test if the bottom-left and bottom-right point also fall - unefficient sleeping code
				Point targetBLPosition = Point(targetPosition.x-halfSize.width, targetPosition.y-halfSize.height);
				Point targetBRPosition = Point(targetPosition.x+halfSize.width, targetPosition.y-halfSize.height);
				if (_pPhysicCollision->collide(targetBLPosition) || _pPhysicCollision->collide(targetBRPosition)) {
					targetPosition.y = (targetPosition.y + currentPosition.y)/2.f;
				} else {
					_eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
					events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
					EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
					delete pChangeStateEvent;
				}
			} else {
				targetPosition = targetBCPosition + Point(0.f, halfSize.height);
			}
		}
	} else {
		targetPosition = currentPosition;
	}

	// Bounding test on the 6 others bounding points
	targetPosition = Point(floor(targetPosition.x), floor (targetPosition.y));
	Point movementDir = targetPosition - currentPosition;
	float movementLength = movementDir.getLength();
	Point movementStep = movementDir.normalize();
	Point centerPos = currentPosition;
	float fStepToExecute = 100000.f;

	//corner points
	Point trPos = Point(centerPos.x+halfSize.width, centerPos.y+halfSize.height);
	Point tlPos = Point(centerPos.x-halfSize.width, centerPos.y+halfSize.height);

	//intermediar lateral point
	Point l1Pos = Point(centerPos.x-halfSize.width, centerPos.y-halfSize.height+thirdSize.height);
	Point l2Pos = Point(centerPos.x-halfSize.width, centerPos.y-halfSize.height+2*thirdSize.height);
	Point r1Pos = Point(centerPos.x+halfSize.width, centerPos.y-halfSize.height+thirdSize.height);
	Point r2Pos = Point(centerPos.x+halfSize.width, centerPos.y-halfSize.height+2*thirdSize.height);

	std::vector<Point> pointToTest;
	if (!_pPhysicCollision->collide(trPos)) { pointToTest.push_back(trPos); }
	if (!_pPhysicCollision->collide(tlPos)) { pointToTest.push_back(tlPos); }
	if (!_pPhysicCollision->collide(l1Pos)) { pointToTest.push_back(l1Pos); }
	if (!_pPhysicCollision->collide(l2Pos)) { pointToTest.push_back(l2Pos); }
	if (!_pPhysicCollision->collide(r1Pos)) { pointToTest.push_back(r1Pos); }
	if (!_pPhysicCollision->collide(r2Pos)) { pointToTest.push_back(r2Pos); }

	std::vector<float> stepsVector;
	for (std::vector<Point>::iterator itPoint=pointToTest.begin(); itPoint!=pointToTest.end(); ++itPoint) {
		float fPossibleStepCount = _pPhysicCollision->countStepToNextPixel(*itPoint, movementStep, false, movementLength);
		stepsVector.push_back(fPossibleStepCount);
	}

	for (std::vector<float>::iterator itStep=stepsVector.begin(); itStep!=stepsVector.end(); ++itStep) {
		if (*itStep < fStepToExecute && *itStep >= 0) {
			fStepToExecute = *itStep;
		}
	}

	if (fStepToExecute == 100000.f) {
		fStepToExecute = movementLength; 
	}

	resPosition = centerPos + (movementStep*fStepToExecute);;
	return eRet;
}

}  // namespace physics
