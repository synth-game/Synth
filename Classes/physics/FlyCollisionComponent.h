#ifndef PHYSICS_FLY_COLLISION_COMPONENT_H
#define PHYSICS_FLY_COLLISION_COMPONENT_H

#include "EventCustom.h"
#include "Physics/CollisionComponent.h"

namespace physics
{
class FlyCollisionComponent : public CollisionComponent
{
public:
	/**
	 * Ne pas faire le test de pente
	 *
	 */
	void onTestCollision(EventCustom* pEvent);

};

}  // namespace physics
#endif
