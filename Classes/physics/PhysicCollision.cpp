#include "PhysicCollision.h"

namespace physics { 

PhysicCollision::PhysicCollision(Image* pBitmask, Point absoluteOriginPosition) 
	: _pLightCollision(nullptr)
	, _pBitmask(pBitmask)
	, _absoluteOriginPosition(absoluteOriginPosition) {

}

PhysicCollision::~PhysicCollision() {
	if (_pLightCollision != nullptr) { delete _pLightCollision; }
	if (_pBitmask != nullptr) { delete _pBitmask; }
}

bool PhysicCollision::collide(Point position) {
	bool bRet = false;

	unsigned char posValue = getValue(convertToImageSpace(position));
	if (posValue == 0) {
		bRet = true;
	}

	if (_pLightCollision != nullptr) {
		if (_pLightCollision->isInWhiteLight(position)) {
			bRet = false;
		}
	}

	return bRet; 
}

Point PhysicCollision::getNextPixel(Point position, Point direction, bool bVoid) {
	Point wantedPixel = position;

	bool bSampleState = !collide(wantedPixel);
	while(bSampleState != bVoid) {
		wantedPixel = wantedPixel + direction;

		// out of image
		if(wantedPixel.x < 0 || wantedPixel.x >= _pBitmask->getWidth() || wantedPixel.y < 0 || wantedPixel.y >= _pBitmask->getHeight()) {
			CCLOG("OUT OF IMAGE COLLISION");
			//wantedPixel = position;
			break;
		}

		bSampleState = !collide(wantedPixel);
	}

	return wantedPixel;
}

float PhysicCollision::countStepToNextPixel(Point position, Point direction, bool bVoid, float fMaxLength) {
	float fRet = 0.f;
	Point wantedPixel = position + direction;

	bool bSampleState = !collide(wantedPixel);
	while(bSampleState != bVoid && fRet < fMaxLength) {
		wantedPixel = wantedPixel + direction;

		// out of image
		if(wantedPixel.x < 0 || wantedPixel.x >= _pBitmask->getWidth() || wantedPixel.y < 0 || wantedPixel.y >= _pBitmask->getHeight()) {
			fRet = 0.f;
			break;
		}

		bSampleState = !collide(wantedPixel);
		++fRet;
	}

	if (fRet >= fMaxLength) {
		fRet = -1.f;
	}

	return fRet;
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
