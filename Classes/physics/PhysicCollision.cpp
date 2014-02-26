#include "PhysicCollision.h"

namespace physics { 

PhysicCollision::PhysicCollision(Image* pBitmask, Point absoluteOriginPosition) 
	: _pBitmask(pBitmask)
	, _absoluteOriginPosition(absoluteOriginPosition) {

		Point nextPos = getNextPixelInDirection(Point(391, 225), 0, EDirection::TOP);
		CCLOG(">> Next Pixel [391|225|RIGHT] : %f, %f", nextPos.x, nextPos.y);
}

PhysicCollision::~PhysicCollision() {
	if (_pBitmask != nullptr) { delete _pBitmask; }
}

Point PhysicCollision::boundingTest(Point nextPosition, EDirection dir) {
	int half_sprite_w = static_cast<int>(floor((_ownerSize.width/2.f) - 0.5f));
	int half_sprite_h = static_cast<int>(floor((_ownerSize.height/2.f) - 0.5f));
	
	Point retPos = nextPosition;
	Point imageSpaceNextPos(nextPosition.x - _absoluteOriginPosition.x, _absoluteOriginPosition.y - nextPosition.y);

	switch(dir) {
	case EDirection::LEFT:
		imageSpaceNextPos.x -= half_sprite_w;
		imageSpaceNextPos = getNextPixelInDirection(imageSpaceNextPos, 255, EDirection::RIGHT);
		retPos.x = _absoluteOriginPosition.x + imageSpaceNextPos.x + half_sprite_w;
		break;

	case EDirection::TOP:
		imageSpaceNextPos.y -= half_sprite_h;
		imageSpaceNextPos = getNextPixelInDirection(imageSpaceNextPos, 255, EDirection::BOTTOM);
		retPos.y = _absoluteOriginPosition.y - imageSpaceNextPos.y - half_sprite_h;
		break;

	case EDirection::RIGHT:
		imageSpaceNextPos.x += half_sprite_w;
		imageSpaceNextPos = getNextPixelInDirection(imageSpaceNextPos, 255, EDirection::LEFT);
		retPos.x = _absoluteOriginPosition.x + imageSpaceNextPos.x - half_sprite_w;
		break;

	case EDirection::BOTTOM:
	default:
		imageSpaceNextPos.y += half_sprite_h;
		imageSpaceNextPos = getNextPixelInDirection(imageSpaceNextPos, 255, EDirection::TOP);
		retPos.y = _absoluteOriginPosition.y - imageSpaceNextPos.y + half_sprite_h;
		break;
	}

	retPos.x = floor(retPos.x);
	retPos.y = floor(retPos.y);

	return retPos;
}

Point PhysicCollision::groundTest(Point currentPosition, Point nextPosition) {
	return Point::ZERO;
}

bool PhysicCollision::isOnGround(Point currentPosition) {
	return false;
}

Point PhysicCollision::getNextPixelInDirection(Point currentPixel, unsigned char wantedValue, EDirection dir) {
	Point direction;
	Point wantedPixel = currentPixel;

	switch(dir) {
	case EDirection::LEFT:
		direction = Point(-1, 0);
		break;

	case EDirection::TOP:
		direction = Point(0, -1);
		break;

	case EDirection::RIGHT:
		direction = Point(1, 0);
		break;

	case EDirection::BOTTOM:
	default:
		direction = Point(0, 1);
		break;
	}

	unsigned char ucValue = getValue(wantedPixel);
	while(ucValue != wantedValue) {
		wantedPixel = wantedPixel + direction;

		// out of image
		if(wantedPixel.x < 0 || wantedPixel.x >= _pBitmask->getWidth() || wantedPixel.y < 0 || wantedPixel.y >= _pBitmask->getHeight()) {
			wantedPixel = currentPixel;
			break;
		}

		ucValue = getValue(wantedPixel);
	}

	return wantedPixel;
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
