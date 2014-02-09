#ifndef PHYSICS_PHYSIC_COLLISION_H
#define PHYSICS_PHYSIC_COLLISION_H

#include "cocos2d.h"

USING_NS_CC;

namespace physics
{
	enum EDirection{NO_DIRECTION};

class PhysicCollision
{
protected:
	Image* _pBitmask;

	Point _absoluteOriginPosition;

	Size _ownerSize;
	
	unsigned char getAlpha(Point pixel);
	Point getNextPixelInDirection(Point currentPixel, unsigned char wantedValue, EDirection dir);

public:
	PhysicCollision(Image* pBitmask, Point absoluteOriginPosition, Size _ownerSize);

	void setOwnerSize(Size size);

	void setBitmask(Image* pBitmask);

	void setAbsoluteOriginPosition(Point pos);
	/**
	 * Test et repousse un pixel de bord du sprite
	 */
	Point boundingTest(Point nextPosition, EDirection dir);

	bool isOnGround(Point currentPosition);

	/**
	 * test de pente : si le personnage est collé à une surface, il doit suivre son relief en se déplaçant contre
	 *
	 *
	 */
	Point groundTest(Point currentPosition, Point nextPosition);

};

}  // namespace physics
#endif
