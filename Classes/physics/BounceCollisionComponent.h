/*!
 * \file BounceCollisionComponent.h
 * \brief The actor bounces on the floor
 * \author Chupee
 * \date 16/03/2014
 */
#ifndef PHYSICS_BOUNCE_COLLISION_COMPONENT_H
#define PHYSICS_BOUNCE_COLLISION_COMPONENT_H


#include "Physics/CollisionComponent.h"

namespace physics {
class BounceCollisionComponent : public CollisionComponent {

public:
	/**
	 * si un point de la bounding box collisionne un mur, changer la vitesse du MovementComponent dans la direction inverse
	 */
	void onTestCollision(EventCustom* pEvent);

};

}  // namespace physics
#endif
