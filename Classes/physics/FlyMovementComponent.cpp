#include "FlyMovementComponent.h"
#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"

namespace physics
{

FlyMovementComponent::FlyMovementComponent()
	: MovementComponent(){
}

FlyMovementComponent* FlyMovementComponent::create(Point acceleration) {
	FlyMovementComponent* pFlyMovementComponent = new FlyMovementComponent();
	if (pFlyMovementComponent != nullptr && pFlyMovementComponent->init()) {
		pFlyMovementComponent->autorelease();
		pFlyMovementComponent->setAcceleration(acceleration);
	} else {
		CC_SAFE_DELETE(pFlyMovementComponent);
	}
	return pFlyMovementComponent;
}

void FlyMovementComponent::onEditMove(EventCustom* pEvent) {
	events::EditMoveEvent* editMoveEvent = static_cast<events::EditMoveEvent*>(pEvent);
	core::SynthActor* eventSource = static_cast<core::SynthActor*>(editMoveEvent->getSource());
	core::SynthActor* componentOwner = static_cast<core::SynthActor*>(_owner);
	this->setGravity(Point(0.0f, 0.0f));
	if (componentOwner == eventSource) {
		if (editMoveEvent->getChangeX()) {
			_direction.x = editMoveEvent->getDirection().x;
		}
		if (editMoveEvent->getChangeY()) {
			_direction.y = editMoveEvent->getDirection().y;
		}
		_bStartMoving = editMoveEvent->isStartMoving();
	}
}

void FlyMovementComponent::onJump(EventCustom* pEvent) {
	// DO NOTHING
}

FlyMovementComponent::~FlyMovementComponent(){
}

void FlyMovementComponent::update(float fDt)
{
}
}  // namespace physics
