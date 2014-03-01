/*!
 * \file FollowMovementComponent.h
 * \brief The actor follows its owner
 * \author Chupee
 * \date 27/02/2014
 */
#ifndef PHYSICS_FOLLOW_MOVEMENT_COMPONENT_H
#define PHYSICS_FOLLOW_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "Physics/MovementComponent.h"

USING_NS_CC;

namespace physics {

/*! \class FollowMovementComponent
 * \brief The actor follows its owner
 *
 * 
 */
class FollowMovementComponent : public MovementComponent {

public:
	/*
	 * Methods
	 */

	FollowMovementComponent* create(Point acceleration, Point target);

protected:

	/*
	 * Methods
	 */

	/**
	 * change the _target attribute with _direction attribute of the event
	 */
	virtual void onEditMove(EventCustom* pEvent)=0;

	/**
	 * Make the movment toward the target position
	 */
	virtual void update(float fDt)=0;


	/*
	 * Members
	 */
	Point _target;

};

}  // namespace physics
#endif
