#include "PhysicCollision.h"

namespace physics
{

Point PhysicCollision::boundingTest(Point nextPosition, EDirection dir)
{
	return Point::ZERO;
}

bool PhysicCollision::isOnGround(Point currentPosition)
{
	return false;
}

Point PhysicCollision::groundTest(Point currentPosition, Point nextPosition)
{
	return Point::ZERO;
}

Point PhysicCollision::getNextPixelInDirection(Point currentPixel, unsigned char wantedValue, EDirection dir)
{
	return Point::ZERO;
}
}  // namespace physics
