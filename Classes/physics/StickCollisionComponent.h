#ifndef PHYSICS_STICK_COLLISION_COMPONENT_H
#define PHYSICS_STICK_COLLISION_COMPONENT_H

#include "EventCustom.h"
#include "Physics/CollisionComponent.h"

namespace Physics
{
class StickCollisionComponent : public CollisionComponent
{
private:
	bool _bIsSticked;


public:
	/**
	 * Si un des points cardinaux collisionne -> faire le test de pente contre la surface correspondante
	 *
	 */
	void onTestCollision(EventCustom* pEvent);

};

}  // namespace Physics
#endif
