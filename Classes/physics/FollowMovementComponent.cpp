/*!
 * \file FollowMovementComponent.cpp
 * \brief The actor follows a target
 * \author Chupee
 * \date 27/02/2014
 */
#include "FollowMovementComponent.h"
#include "core/SynthActor.h"
#include "physics/GeometryComponent.h"
#include "physics/CollisionComponent.h"
#include "game/NodeOwnerComponent.h"
#include "graphics/AnimatedSpriteComponent.h"

#include "events/ChangeTargetEvent.h"
#include "events/ChangePositionEvent.h"
#include "events/TestCollisionEvent.h"


namespace physics {

FollowMovementComponent::FollowMovementComponent()
	: MovementComponent(),
	_target(nullptr) {
}

FollowMovementComponent::~FollowMovementComponent() {

}

bool FollowMovementComponent::init() {
	SynthComponent::init(MovementComponent::COMPONENT_TYPE);
	return true;
}

FollowMovementComponent* FollowMovementComponent::create(Point acceleration, core::SynthActor* target) {
	FollowMovementComponent* pFollowMovementComponent = new FollowMovementComponent();
	if (pFollowMovementComponent != nullptr && pFollowMovementComponent->init()) {
		pFollowMovementComponent->autorelease();
		pFollowMovementComponent->setAcceleration(acceleration);
		pFollowMovementComponent->setTarget(target);
	} else {
		CC_SAFE_DELETE(pFollowMovementComponent);
	}
	return pFollowMovementComponent;
}

void FollowMovementComponent::initListeners() {
	// Listeners initialization
	_pChangeTargetEventListener = EventListenerCustom::create(events::ChangeTargetEvent::EVENT_NAME, CC_CALLBACK_1(FollowMovementComponent::onChangeTarget, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeTargetEventListener, 1);
}

void FollowMovementComponent::onChangeTarget(EventCustom* pEvent) {
	events::ChangeTargetEvent* pChangeTargetEvent				= static_cast<events::ChangeTargetEvent*>(pEvent);
    core::SynthActor* pSource									= static_cast<core::SynthActor*>(pChangeTargetEvent->getSource());
    core::SynthActor* pOwner									= static_cast<core::SynthActor*>(_owner);
	core::SynthActor* newTarget									= pChangeTargetEvent->getNewTarget();

	if (pSource->getActorID() == pOwner->getActorID()) {
		setTarget(newTarget);
    } else {
        CCLOG("TOGGLE LIGHT EVENT RECEIVED BUT ID NOT THE SAME");
    }
}

void FollowMovementComponent::update( float fDt ) {

	if( _owner != _target) {

		physics::GeometryComponent* pOwnerGeometryComponent = static_cast<physics::GeometryComponent*>(_target->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
		CCASSERT(pOwnerGeometryComponent != nullptr, "FollowMovementComponent needs a GeometryComponent added to the owner of the actor");

		physics::GeometryComponent* pOwnedGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
		CCASSERT(pOwnedGeometryComponent != nullptr, "FollowMovementComponent needs a GeometryComponent added to its actor");

		graphics::SpriteComponent* pOwnerSpriteComponent = static_cast<graphics::SpriteComponent*>(_target->getComponent(graphics::SpriteComponent::COMPONENT_TYPE));
		CCASSERT(pOwnerSpriteComponent != nullptr, "FollowMovementComponent needs a AnimatedSpriteComponent added to the owner of its actor");

		graphics::SpriteComponent* pOwnedSpriteComponent = static_cast<graphics::SpriteComponent*>(_owner->getComponent(graphics::SpriteComponent::COMPONENT_TYPE));
		CCASSERT(pOwnerSpriteComponent != nullptr, "FollowMovementComponent needs a AnimatedSpriteComponent added to the actor");

		Point relativeTarget = Point::ZERO;
		if(pOwnerSpriteComponent->getSprite()->isFlippedX()) {
			relativeTarget = Point(20.f, 0.f);
		} else {
			relativeTarget = Point(-20.f, 0.f);
		}

		if(pOwnerGeometryComponent->getPosition().x < pOwnedGeometryComponent->getPosition().x) {
			pOwnedSpriteComponent->getSprite()->setFlippedX(true);
		} else {
			pOwnedSpriteComponent->getSprite()->setFlippedX(false);
		}

		Point target = Point(pOwnerGeometryComponent->getPosition().x + relativeTarget.x - pOwnedGeometryComponent->getPosition().x, pOwnerGeometryComponent->getPosition().y + relativeTarget.y - pOwnedGeometryComponent->getPosition().y);
		if (abs(target.x) < 20.f && abs(target.y) < 20.f) {
			target = Point::ZERO;
		} else if ( target.getLength() > 30 ) {
			target = target.normalize() * 30;
		}
		Point nextPosition = pOwnedGeometryComponent->getPosition() + Point(target.x * _acceleration.x, target.y * _acceleration.y) * fDt;
	
		physics::CollisionComponent* pCollisionComponent = static_cast<physics::CollisionComponent*>(_owner->getComponent(physics::CollisionComponent::COMPONENT_TYPE));
		if (pCollisionComponent == nullptr) {
			//CCLOG("envoie evenemnt, position %2.f, %2.f", nextPosition.x, nextPosition.y);
			events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, nextPosition);
			EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
		} else {
			events::TestCollisionEvent* pTestCollisionEvent = new events::TestCollisionEvent(_owner, pOwnedGeometryComponent->getPosition(), nextPosition, pOwnedGeometryComponent->getSize());
			EventDispatcher::getInstance()->dispatchEvent(pTestCollisionEvent);
		}
	}
}

}  // namespace physics
