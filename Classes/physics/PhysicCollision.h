#ifndef PHYSICS_PHYSIC_COLLISION_H
#define PHYSICS_PHYSIC_COLLISION_H

#include "Point.h"
#include "Physics/Collision.h"
#include "Physics/EDirection.h"

namespace physics
{
class PhysicCollision : public Collision
{
protected:
	Point getNextPixelInDirection(Point currentPixel, unsigned char wantedValue, EDirection dir);

public:
	/**
	 * Test et repousse un pixel de bord du sprite
	 */
	Point boundingTest(Point nextPosition, EDirection dir);

	bool isOnGround(Point currentPosition);

	/**
	 * test de pente : si le personnage est collé à une surface, il doit suivre son relief en se déplaçant contre
	 *
	 *
	 */
	Point groundTest(Point currentPosition, Point nextPosition);

};

}  // namespace physics
#endif
