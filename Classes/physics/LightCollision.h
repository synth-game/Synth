#ifndef PHYSICS_LIGHT_COLLISION_H
#define PHYSICS_LIGHT_COLLISION_H

#include <vector>
#include "cocos2d.h"
#include "core/SynthActor.h"

USING_NS_CC;

namespace physics
{
class LightCollision
{
private:
	std::vector<core::SynthActor*> _lightCollection;


public:
	/**
	 *
	 */
	LightCollision(std::vector<core::SynthActor*> lightCollection);

	Color4B getPixelColor(Point pixel);

};

}  // namespace physics
#endif
