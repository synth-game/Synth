#ifndef PHYSICS_STICK_MOVEMENT_COMPONENT_H
#define PHYSICS_STICK_MOVEMENT_COMPONENT_H

#include "EventCustom.h"
#include "Point.h"
#include "Physics/MovementComponent.h"
#include "Physics/FollowMovementComponent.h"

namespace physics
{
class StickMovementComponent : public MovementComponent
{
protected:
	void onEditMove(EventCustom* pEvent);

	void update(float fDt);

public:
	static FollowMovementComponent* create();

	void setGravity(Point gravity);

};

}  // namespace physics
#endif
