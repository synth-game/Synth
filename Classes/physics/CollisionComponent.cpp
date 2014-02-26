/*!
 * \file CollisionComponent.cpp
 * \brief Allow and compute collisions
 * \author Jijidici
 * \date 20/02/2014
 */
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
			// boundings collision
			_pPhysicCollision->setOwnerSize(pTestColEvent->getSize());
			Point targetPosition = pTestColEvent->getTargetPosition();

			Point bCollisionPosition = _pPhysicCollision->boundingTest(targetPosition, PhysicCollision::EDirection::BOTTOM);
			Point tCollisionPosition = _pPhysicCollision->boundingTest(targetPosition, PhysicCollision::EDirection::TOP);
			Point lCollisionPosition = _pPhysicCollision->boundingTest(targetPosition, PhysicCollision::EDirection::LEFT);
			Point rCollisionPosition = _pPhysicCollision->boundingTest(targetPosition, PhysicCollision::EDirection::RIGHT);

			bool bVerticalCollision = false;
			Point collidePosition = targetPosition;

			if (bCollisionPosition.y != targetPosition.y) {
				collidePosition.y = bCollisionPosition.y;
				bVerticalCollision = true;
			} else if (tCollisionPosition.y != targetPosition.y) {
				collidePosition.y = tCollisionPosition.y;
				bVerticalCollision = true;
			}

			if (lCollisionPosition.x != targetPosition.x) {
				collidePosition.x = lCollisionPosition.x;
			} else if (rCollisionPosition.x != targetPosition.x) {
				collidePosition.x = rCollisionPosition.x;
			}

			if (!collidePosition.equals(pTestColEvent->getCurrentPosition())) {
				events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, collidePosition);
				EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
			}

			if (bVerticalCollision) {
				// TO DO : Send InteruptMoveEvent <- hit a wall
			}
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
