#ifndef PHYSICS_BOUNCE_COLLISION_COMPONENT_H
#define PHYSICS_BOUNCE_COLLISION_COMPONENT_H

#include "EventCustom.h"
#include "Physics/CollisionComponent.h"

namespace Physics
{
class BounceCollisionComponent : public CollisionComponent
{
public:
	/**
	 * si un point de la bounding box collisionne un mur, changer la vitesse du MovementComponent dans la direction inverse
	 */
	void onTestCollision(EventCustom* pEvent);

};

}  // namespace Physics
#endif
