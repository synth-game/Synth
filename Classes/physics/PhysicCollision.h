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
	enum EDirection{
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
		NO_DIRECTION
	};

	PhysicCollision(Image* pBitmask, Point absoluteOriginPosition);
	~PhysicCollision();

	void setBitmask(Image* pBitmask) { _pBitmask = pBitmask; }
	void setAbsoluteOriginPosition(Point pos) { _absoluteOriginPosition = pos; }
	
	bool collide(Point position);

protected:
	Point convertToImageSpace(Point absolutePos);
	Point getNextPixelInDirection(Point currentPixel, unsigned char wantedValue, EDirection dir);
	unsigned char getValue(Point pixel);
	

	Image* _pBitmask;
	Point _absoluteOriginPosition;
	Size _ownerSize;
};

}  // namespace physics
#endif
