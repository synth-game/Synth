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

unsigned char PhysicCollision::getValue(Point pixel) {
	CCASSERT(pixel.x >= 0 , "PhysicCollision : Out of array search for pixel value.");
	CCASSERT(pixel.x < _pBitmask->getWidth() , "PhysicCollision : Out of array search for pixel value.");
	CCASSERT(pixel.y >= 0 , "PhysicCollision : Out of array search for pixel value.");
	CCASSERT(pixel.y < _pBitmask->getHeight() , "PhysicCollision : Out of array search for pixel value.");

	int iX = static_cast<int>(pixel.x);
	int iY = static_cast<int>(pixel.y);
	return _pBitmask->getData()[4*(iX + iY*_pBitmask->getWidth())];
}

}  // namespace physics
