#include "PhysicCollision.h"

namespace physics { 

PhysicCollision::PhysicCollision(Image* pBitmask, Point absoluteOriginPosition) 
	: _pBitmask(pBitmask)
	, _absoluteOriginPosition(absoluteOriginPosition) {

}

PhysicCollision::~PhysicCollision() {
	if (_pBitmask != nullptr) { delete _pBitmask; }
}

bool PhysicCollision::collide(Point position) {
	bool bRet = false;

	unsigned char posValue = getValue(convertToImageSpace(position));
	if(posValue == 0) {
		bRet = true;
	}
	return bRet; 
}

Point PhysicCollision::getNextVoidPixel(Point position, EDirection dir) {
	return convertToWorldSpace(getNextPixelInDirection(convertToImageSpace(position), 255, dir));
}

Point PhysicCollision::getNextWallPixel(Point position, EDirection dir) {
	return convertToWorldSpace(getNextPixelInDirection(convertToImageSpace(position), 0, dir));
}

Point PhysicCollision::convertToImageSpace(Point absolutePos) {
	Point imageSpacePosition;
	imageSpacePosition.x = absolutePos.x;
	imageSpacePosition.y = _absoluteOriginPosition.y - absolutePos.y;
	return imageSpacePosition;
}

Point PhysicCollision::convertToWorldSpace(Point imageSpacePos) {
	Point worldSpacePosition;
	worldSpacePosition.x = imageSpacePos.x;
	worldSpacePosition.y = _absoluteOriginPosition.y - imageSpacePos.y;
	return worldSpacePosition;
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
