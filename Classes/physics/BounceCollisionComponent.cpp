/*!
 * \file BounceCollisionComponent.h
 * \brief The actor bounces on the floor
 * \author Chupee
 * \date 16/03/2014
 */
#include "BounceCollisionComponent.h"
#include <cmath>
#include <string>
#include <vector>
#include "core/SynthActor.h"
#include "events/ChangePositionEvent.h"
#include "events/ChangeStateEvent.h"
#include "events/JumpEvent.h"
#include "events/CollisionEvent.h"
namespace physics {

BounceCollisionComponent::BounceCollisionComponent()
	: CollisionComponent() {
}

BounceCollisionComponent::~BounceCollisionComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pTestCollisionEventListener);
	EventDispatcher::getInstance()->removeEventListener(_pChangeStateCollision);
}

BounceCollisionComponent* BounceCollisionComponent::create() {
	BounceCollisionComponent* pCollisionComponent = new BounceCollisionComponent();
	if (pCollisionComponent != nullptr && pCollisionComponent->init()) {
		pCollisionComponent->autorelease();
	} else {
		CC_SAFE_DELETE(pCollisionComponent);
	}
	return pCollisionComponent;
}

void BounceCollisionComponent::initListeners() {
	// Listeners initialization
	_pTestCollisionEventListener = EventListenerCustom::create(events::TestCollisionEvent::EVENT_NAME, CC_CALLBACK_1(BounceCollisionComponent::onTestCollision, this));
	_pChangeStateCollision = EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(CollisionComponent::onChangeState, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pTestCollisionEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeStateCollision, 1);
}

void BounceCollisionComponent::onTestCollision(EventCustom* pEvent) {
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

			events::JumpEvent* pMoveEvent = nullptr;
			if (eCollision == VERTICAL) {
				Point direction = Point::ZERO;
				// if the collision is towards the ground
				if ((pTestColEvent->getCurrentPosition().y - pTestColEvent->getTargetPosition().y) > 0  ) {
					direction = Point(0, 1);
				// if it is towards the sky
				} else {
					direction = Point(0, -1);
				}
				pMoveEvent = new events::JumpEvent(_owner, direction, true);
				EventDispatcher::getInstance()->dispatchEvent(pMoveEvent);
			} else if (eCollision == HORIZONTAL) {
				Point direction = Point::ZERO;
				// if the collision is towards the left
				if ((pTestColEvent->getCurrentPosition().x - pTestColEvent->getTargetPosition().x) > 0  ) {
					direction = Point(1, 0);
				// if it is towards the right
				} else {
					direction = Point(-1, 0);
				}
				pMoveEvent = new events::JumpEvent(_owner, direction, true);
				EventDispatcher::getInstance()->dispatchEvent(pMoveEvent);
			}
			// send CollisionEvent for sound and graphic components
			events::CollisionEvent* pCollisionEvent = new events::CollisionEvent(_owner);
			EventDispatcher::getInstance()->dispatchEvent(pCollisionEvent);
		}

		//check if the component have a LightCollision
		LightCollision* pLightCollision = _pPhysicCollision->getLightCollision();
		if (pLightCollision != nullptr) {
			Color4B aL = pLightCollision->getCurrentColor(computingPos);
		}

		// Change position
		if (!pTestColEvent->getCurrentPosition().equals(computingPos)) {
            events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, computingPos);
            EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
        }

    }
}

}  // namespace physics
