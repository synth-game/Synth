/*!
 * \file MovementComponent.h
 * \brief Fly collision component
 * \author Tom Duchene
 * \date 14/03/2014
 */

#ifndef PHYSICS_FLY_COLLISION_COMPONENT_H
#define PHYSICS_FLY_COLLISION_COMPONENT_H


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
