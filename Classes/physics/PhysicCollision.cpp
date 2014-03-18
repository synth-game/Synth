#include "PhysicCollision.h"

#include <algorithm>

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
			wantedPixel = Point(-5.f, -5.f);
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
			fRet = fMaxLength;
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

float PhysicCollision::computeSurfaceSlope(Point surfaceSample) {
	float fRet = 100000.f;

	if (collide(surfaceSample) && collide(surfaceSample)) {
		Point secondSurfaceSample = getBelowSurfacePixel(surfaceSample, 5.f);

		if (secondSurfaceSample.x > surfaceSample.x) {
			fRet = (surfaceSample.y - secondSurfaceSample.y)/(surfaceSample.x - secondSurfaceSample.x);
		} else if ( secondSurfaceSample.x < surfaceSample.x ) {
			fRet = (secondSurfaceSample.y - surfaceSample.y)/(secondSurfaceSample.x - surfaceSample.x);
		}
	}
	
	return fRet;
}

Point PhysicCollision::getBelowSurfacePixel(Point surfacePos, float distance) {
	Point pos1 = surfacePos;
	Point pos2 = Point(pos1.x, std::max(pos1.y-distance, 0.f));
	
	Point lNearestVoidPixel = getNextPixel(pos1, Point(-1.f, 0.f), true);
	Point rNearestVoidPixel = getNextPixel(pos1, Point( 1.f, 0.f), true);

	Point dir = Point(-1.f, 0.f);
	if (abs(pos1.x - rNearestVoidPixel.x) < abs(pos1.x - lNearestVoidPixel.x)) {
		dir.x = 1.f;
	}

	pos2 = getNextPixel(pos2, dir, true);
	return pos2;
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
	unsigned char ucRet = 255;

	int iX = static_cast<int>(pixel.x);
	int iY = static_cast<int>(pixel.y);
	if(iX>=0 && iX<_pBitmask->getWidth() && iY>=0 && iY<_pBitmask->getHeight()) {
		ucRet = _pBitmask->getData()[4*(iX + iY*_pBitmask->getWidth())];
	}

	return ucRet;
}

}  // namespace physics
