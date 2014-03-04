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

namespace physics {

const char* CollisionComponent::COMPONENT_TYPE = "CollisionComponent";

CollisionComponent::CollisionComponent() 
	: SynthComponent()
	, _pPhysicCollision(nullptr)
	, _pLightCollision(nullptr)
	, _pTestCollisionEventListener(nullptr) {
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
			boundingTest(pTestColEvent, computingPos);
		}

		// Change position 
		events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, computingPos);
		EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
	}
}

bool CollisionComponent::init() {
	SynthComponent::init(CollisionComponent::COMPONENT_TYPE);
	return true;
}

void CollisionComponent::initListeners() {
	// Listeners initialization
	_pTestCollisionEventListener = EventListenerCustom::create(events::TestCollisionEvent::EVENT_NAME, CC_CALLBACK_1(CollisionComponent::onTestCollision, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pTestCollisionEventListener, 1);
}

bool CollisionComponent::boundingTest(events::TestCollisionEvent* initiatorEvent, Point& resPosition) {
	bool bRet = false;

	// build position-target vector
	Point currentPosition = Point(floor(initiatorEvent->getCurrentPosition().x), floor(initiatorEvent->getCurrentPosition().y));
	Point targetPosition = Point(floor(initiatorEvent->getTargetPosition().x), floor(initiatorEvent->getTargetPosition().y));
	Point movementDir = targetPosition - currentPosition;
	float movementLength = movementDir.getLength();
	Point movementStep = movementDir.normalize();
	Size halfSize = initiatorEvent->getSize()/2;
	Size thirdSize = initiatorEvent->getSize()/3;
			
	Point centerPos = currentPosition;

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

		// case of hypothetical landing
		if(_pPhysicCollision->collide(blPos) || _pPhysicCollision->collide(brPos)) {
			bRet = true;
			//test if bottom-center point collide the ground
			while((centerPos-currentPosition).getLength() < movementLength) {
				nextCenterPos = centerPos + movementStep;
				Point bcPos = Point(nextCenterPos.x, nextCenterPos.y-halfSize.height);

				if(_pPhysicCollision->collide(bcPos)) {
					bRet = false;
					break;
				}
				centerPos = nextCenterPos;
			}

			break;
		} else if(_pPhysicCollision->collide(trPos)
			   || _pPhysicCollision->collide(tlPos)
			   || _pPhysicCollision->collide(l1Pos)
			   || _pPhysicCollision->collide(l2Pos)
			   || _pPhysicCollision->collide(r1Pos)
			   || _pPhysicCollision->collide(r2Pos)) {
			bRet = true;
			break;
		}
		centerPos = nextCenterPos;
	}

	resPosition = centerPos;
	return bRet;
}

}  // namespace physics
