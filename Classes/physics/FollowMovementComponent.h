#ifndef PHYSICS_FOLLOW_MOVEMENT_COMPONENT_H
#define PHYSICS_FOLLOW_MOVEMENT_COMPONENT_H

#include "Point.h"
#include "EventCustom.h"
#include "Physics/FlyMovementComponent.h"
#include "Physics/MovementComponent.h"

namespace Physics
{
class FollowMovementComponent : public FlyMovementComponent, public MovementComponent
{
protected:
	Point _target;


protected:
	/**
	 * change the _target attribute with _direction attribute of the event
	 */
	virtual void onEditMove(EventCustom* pEvent)=0;

	/**
	 * Make the movment toward the target position
	 */
	virtual void update(float fDt)=0;

public:
	FollowMovementComponent* create(Point acceleration, Point target);

};

}  // namespace Physics
#endif
