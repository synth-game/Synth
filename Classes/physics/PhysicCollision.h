/*!
 * \file PhysicCollision.h
 * \brief Manage collision with the level bitmask
 * \author Jijidici
 * \date 20/02/2014
 */
#ifndef PHYSICS_PHYSIC_COLLISION_H
#define PHYSICS_PHYSIC_COLLISION_H

#include "cocos2d.h"
#include "physics/LightCollision.h"

USING_NS_CC;

namespace physics {

/*!
 * \brief Manage collision with the level bitmask
 */
class PhysicCollision {
public:
	PhysicCollision(Image* pBitmask, Point absoluteOriginPosition);
	~PhysicCollision();

	inline void setLightCollision(LightCollision* pLightCollision) { _pLightCollision = pLightCollision; }
	inline void setBitmask(Image* pBitmask) { _pBitmask = pBitmask; }
	inline void setAbsoluteOriginPosition(Point pos) { _absoluteOriginPosition = pos; }
	inline LightCollision* getLightCollision() { return _pLightCollision; }
	
	bool collide(Point position);
	Point getNextPixel(Point position, Point direction, bool bVoid);
	float countStepToNextPixel(Point position, Point direction, bool bVoid, float fMaxLength);
	float computeSurfaceSlope(Point surfaceSample);
	Point getBelowSurfacePixel(Point pos, float distance);

protected:
	Point convertToImageSpace(Point absolutePos);
	Point convertToWorldSpace(Point imageSpacePos);
	unsigned char getValue(Point pixel);
	
	LightCollision* _pLightCollision;
	Image* _pBitmask;
	Point _absoluteOriginPosition;
};

}  // namespace physics
#endif
