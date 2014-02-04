#ifndef PHYSICS_LIGHT_COLLISION_H
#define PHYSICS_LIGHT_COLLISION_H

#include "vector.h"
#include "Actor.h"
#include "Color4B.h"
#include "Point.h"
#include "Physics/Collision.h"

namespace Physics
{
class LightCollision : public Collision
{
private:
	vector<Actor*> _lightCollection;


public:
	/**
	 *  
	 */
	LightCollision(vector<Actor*> lightCollection);

	Color4B getPixelColor(Point pixel);

};

}  // namespace Physics
#endif
