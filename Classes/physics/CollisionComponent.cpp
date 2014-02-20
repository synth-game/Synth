/*!
 * \file CollisionComponent.cpp
 * \brief Allow and compute collisions
 * \author Jijidici
 * \date 20/02/2014
 */
#include "CollisionComponent.h"
#include "events/TestCollisionEvent.h"

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
