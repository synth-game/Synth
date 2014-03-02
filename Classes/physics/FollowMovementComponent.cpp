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

#include "events/EditMoveEvent.h"
#include "events/ChangePositionEvent.h"
#include "events/TestCollisionEvent.h"

#define MAX_X_SPEED 200.f
#define MAX_Y_SPEED 300.f
#define MAX_JUMP_SPEED 300.f
#define MIN_JUMP_SPEED 150.f

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
	_pEditMoveEventListener = EventListenerCustom::create(events::EditMoveEvent::EVENT_NAME, CC_CALLBACK_1(FollowMovementComponent::onEditMove, this));

	// Add listeners to dispacher
	//EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEditMoveEventListener, 1);
}

void FollowMovementComponent::onEditMove(EventCustom* pEvent) {
	events::EditMoveEvent* editMoveEvent = static_cast<events::EditMoveEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(editMoveEvent->getSource());
	game::NodeOwnerComponent* pNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(eventSource->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	CCASSERT(pNodeOwnerComponent != nullptr, "FollowMovementComponent needs a NodeOwnerComponent added to the owner of the actor");

	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	physics::GeometryComponent* pOwnerGeometryComponent = static_cast<physics::GeometryComponent*>(eventSource->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pNodeOwnerComponent != nullptr, "FollowMovementComponent needs a GeometryComponent added to the owner of the actor");

	core::SynthActor* ownedNode = static_cast<core::SynthActor*>(pNodeOwnerComponent->getOwnedNode());
	physics::GeometryComponent* pOwnedGeometryComponent = static_cast<physics::GeometryComponent*>(ownedNode->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pNodeOwnerComponent != nullptr, "FollowMovementComponent needs a GeometryComponent added to its actor");

	if (componentOwner == ownedNode) {
		Point target = Point(pOwnerGeometryComponent->getPosition().x - pOwnedGeometryComponent->getPosition().x, pOwnerGeometryComponent->getPosition().y - pOwnedGeometryComponent->getPosition().y).normalize();
		CCLOG("TARGET OF FOLLOW MOVEMENT : %f,%f", target.x, target.y);
		//_target = target;
		_bStartMoving = editMoveEvent->isStartMoving();
	}
}

void FollowMovementComponent::update( float fDt ) {

	physics::GeometryComponent* pOwnerGeometryComponent = static_cast<physics::GeometryComponent*>(_target->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pOwnerGeometryComponent != nullptr, "FollowMovementComponent needs a GeometryComponent added to the owner of the actor");

	physics::GeometryComponent* pOwnedGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pOwnedGeometryComponent != nullptr, "FollowMovementComponent needs a GeometryComponent added to its actor");

	//// compute next speed
	//_speed = _speed + Point(_target.x * _acceleration.x, _target.y * _acceleration.y);
 //   
	//// cap the next lateral speed
	//if (_bStartMoving) {
	//	if (abs(_speed.x) > MAX_X_SPEED) {
	//		_speed.x = _direction.x * MAX_X_SPEED;
	//	}
	//} else {
	//	if (_speed.x * _direction.x > 0.f) {
	//		_speed.x = 0.f;
	//	}
	//}

	//if (_speed.y < - MAX_Y_SPEED) {
	//	_speed.y = -MAX_Y_SPEED;
	//}
	//if (_speed.y > MAX_Y_SPEED) {
	//	_speed.y = MAX_Y_SPEED;
	//}
	//// compute next position
	//physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	//CCASSERT(pGeometryComponent != nullptr, "MovementComponent needs a GeometryComponent added to its owner");

	//CCLOG("FOLLOW MOVEMENT GEOMETRY POSITION =========== %f, %f", pGeometryComponent->getPosition().x, pGeometryComponent->getPosition().y);
	//CCLOG("FOLLOW MOVEMENT SPEED AFTER SEUILLAGE =========== %f, %f", _speed.x, _speed.y);
	//CCLOG("FOLLOW MOVEMENT SPEED AFTER SEUILLAGE AND FDT =========== %f, %f", _speed.x*fDt, _speed.y*fDt);
	//Point nextPosition = pGeometryComponent->getPosition() + (_speed * fDt);
	//CCLOG("FOLLOW MOVEMENT NEXT POSITION =========== %f, %f", nextPosition.x, nextPosition.y);
	//nextPosition.x = floor(nextPosition.x);
	//nextPosition.y = floor(nextPosition.y);
	//CCLOG("FOLLOW MOVEMENT NEXT POSITION =========== %f, %f", nextPosition.x, nextPosition.y);

	Point target = Point(pOwnerGeometryComponent->getPosition().x-60.f - pOwnedGeometryComponent->getPosition().x, pOwnerGeometryComponent->getPosition().y - pOwnedGeometryComponent->getPosition().y);
	CCLOG("FOLLOW MOVEMENT TARGET =========== %f, %f", abs(target.x), abs(target.y));
	if (abs(target.x) < 20.f && abs(target.y) < 20.f) {
		target = Point::ZERO;
	} else {
		target = target.normalize();
	}
	CCLOG("FOLLOW MOVEMENT TARGET ZERO ? =========== %f, %f", abs(target.x), abs(target.y));
	Point nextPosition = pOwnedGeometryComponent->getPosition() + Point(target.x * _acceleration.x, target.y * _acceleration.y);
	CCLOG("FOLLOW MOVEMENT NEXT POSITION =========== %f, %f", nextPosition.x, nextPosition.y);
	

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

}  // namespace physics
