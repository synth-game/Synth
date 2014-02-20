#include "PhysicCollision.h"

namespace physics { 

PhysicCollision::PhysicCollision(Image* pBitmask, Point absoluteOriginPosition) 
	: _pBitmask(pBitmask)
	, _absoluteOriginPosition(absoluteOriginPosition) {
}

PhysicCollision::~PhysicCollision() {
	if (_pBitmask != nullptr) { delete _pBitmask; }
}

Point PhysicCollision::boundingTest(Point nextPosition, EDirection dir) {
	return Point::ZERO;
}

Point PhysicCollision::groundTest(Point currentPosition, Point nextPosition) {
	return Point::ZERO;
}

bool PhysicCollision::isOnGround(Point currentPosition) {
	return false;
}

Point PhysicCollision::getNextPixelInDirection(Point currentPixel, unsigned char wantedValue, EDirection dir) {
	return Point::ZERO;
}

unsigned char PhysicCollision::getAlpha(Point pixel) {
	return 0;
}

}  // namespace physics
