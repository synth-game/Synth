#ifndef PHYSICS_STICK_MOVEMENT_COMPONENT_H
#define PHYSICS_STICK_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "Physics/MovementComponent.h"

USING_NS_CC;

namespace physics
{
class StickMovementComponent : public MovementComponent
{
protected:
	void onEditMove(EventCustom* pEvent);

	void update(float fDt);

public:
	static StickMovementComponent* create();

	void setGravity(Point gravity);

};

}  // namespace physics
#endif
