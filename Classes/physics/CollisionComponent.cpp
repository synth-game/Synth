/*!
 * \file CollisionComponent.cpp
 * \brief Allow and compute collisions
 * \author Jijidici
 * \date 20/02/2014
 */
#include <cmath>
#include "CollisionComponent.h"
#include "core/SynthActor.h"
#include "events/TestCollisionEvent.h"
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
		// check if the component have a PhysicCollision
		if (_pPhysicCollision != nullptr) {
			// build position-target vector
			Point currentPosition = Point(floor(pTestColEvent->getCurrentPosition().x), floor(pTestColEvent->getCurrentPosition().y));
			Point targetPosition = Point(floor(pTestColEvent->getTargetPosition().x), floor(pTestColEvent->getTargetPosition().y));
			Point movementDir = targetPosition - currentPosition;
			float movementLength = movementDir.getLength();
			Point movementStep = movementDir.normalize();
			
			Point centerPos = pTestColEvent->getCurrentPosition();

			// test pixel by pixel the center point movement - stop if collide
			while((centerPos - pTestColEvent->getCurrentPosition()).getLength() < movementLength) {
				Point nextCenterPos = centerPos + movementStep;

				if(_pPhysicCollision->collide(nextCenterPos)) {
					break;
				}
				centerPos = nextCenterPos;
			}

			// send the collided position
			events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, centerPos);
			EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
		} else {
			// Change position without modification
			events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, pTestColEvent->getTargetPosition());
			EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
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

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pTestCollisionEventListener, 1);
}

}  // namespace physics
