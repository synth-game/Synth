#ifndef PHYSICS_FLY_MOVEMENT_COMPONENT_H
#define PHYSICS_FLY_MOVEMENT_COMPONENT_H

#include "EventCustom.h"
#include "Point.h"
#include "Physics/MovementComponent.h"

namespace physics
{
class FlyMovementComponent : public MovementComponent
{
protected:
	/**
	 * Make normal movment sur l'axe y
	 */
	virtual void onEditMove(EventCustom* pEvent)=0;

	/**
	 * Disable jump
	 */
	virtual void onJump(EventCustom* pEvent)=0;

	/**
	 *
	 */
	void update(float fDt);

public:
	static FlyMovementComponent* create(Point acceleration);

};

}  // namespace physics
#endif
