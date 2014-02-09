#include "PhysicCollision.h"

namespace physics
{

PhysicCollision::PhysicCollision(Image* pBitmask, Point absoluteOriginPosition, Size _ownerSize)
{
}

void PhysicCollision::setOwnerSize(Size size)
{
}

unsigned char PhysicCollision::getAlpha(Point pixel)
{
	return 0;
}

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
