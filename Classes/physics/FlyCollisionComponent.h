#ifndef PHYSICS_FLY_COLLISION_COMPONENT_H
#define PHYSICS_FLY_COLLISION_COMPONENT_H

#include "EventCustom.h"
#include "Physics/CollisionComponent.h"

namespace Physics
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

}  // namespace Physics
#endif
