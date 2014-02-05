#ifndef PHYSICS_LIGHT_COLLISION_H
#define PHYSICS_LIGHT_COLLISION_H

#include <vector>
#include "Actor.h"
#include "Color4B.h"
#include "Point.h"
#include "Physics/Collision.h"

namespace physics
{
class LightCollision : public Collision
{
private:
	std::vector<Actor*> _lightCollection;


public:
	/**
	 *
	 */
	LightCollision(std::vector<Actor*> lightCollection);

	Color4B getPixelColor(Point pixel);

};

}  // namespace physics
#endif
