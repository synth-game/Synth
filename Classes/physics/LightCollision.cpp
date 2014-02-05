#include "LightCollision.h"

#include "core/SynthActor.h"

namespace physics
{

LightCollision::LightCollision(std::vector<core::SynthActor*> lightCollection)
{
}

Color4B LightCollision::getPixelColor(Point pixel)
{
	return Color4B::BLACK;
}
}  // namespace physics
