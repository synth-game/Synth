#ifndef PHYSICS_COLLISION_H
#define PHYSICS_COLLISION_H

#include "Point.h"
#include "Size.h"
#include "Physics/Image.h"

namespace Physics
{
class Collision
{
private:
	Image* _pBitmask;

	Point _absoluteOriginPosition;

	Size _ownerSize;


protected:
	unsigned char getAlpha(Point pixel);

public:
	/**
	 *  
	 */
	Collision(Image* pBitmask, Point absoluteOriginPosition, Size _ownerSize);

	void setOwnerSize(Size size);

};

}  // namespace Physics
#endif
