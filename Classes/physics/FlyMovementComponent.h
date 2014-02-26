#ifndef PHYSICS_FLY_MOVEMENT_COMPONENT_H
#define PHYSICS_FLY_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "Physics/MovementComponent.h"

USING_NS_CC;

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
