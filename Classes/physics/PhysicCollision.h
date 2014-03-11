/*!
 * \file PhysicCollision.h
 * \brief Manage collision with the level bitmask
 * \author Jijidici
 * \date 20/02/2014
 */
#ifndef PHYSICS_PHYSIC_COLLISION_H
#define PHYSICS_PHYSIC_COLLISION_H

#include "cocos2d.h"

USING_NS_CC;

namespace physics {

/*!
 * \brief Manage collision with the level bitmask
 */
class PhysicCollision {
public:
	PhysicCollision(Image* pBitmask, Point absoluteOriginPosition);
	~PhysicCollision();

	void setBitmask(Image* pBitmask) { _pBitmask = pBitmask; }
	void setAbsoluteOriginPosition(Point pos) { _absoluteOriginPosition = pos; }
	
	bool collide(Point position);

	inline int getZoneWidth() { return _pBitmask->getWidth(); }
	inline int getZoneHeight() { return _pBitmask->getHeight(); }

protected:
	Point convertToImageSpace(Point absolutePos);
	Point convertToWorldSpace(Point imageSpacePos);
	unsigned char getValue(Point pixel);
	

	Image* _pBitmask;
	Point _absoluteOriginPosition;
};

}  // namespace physics
#endif
