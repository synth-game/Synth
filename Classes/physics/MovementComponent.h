/* *****************************************************
 *		MovementComponent.h - @ Jeremie Defaye - 02/02/14
 ***************************************************** */

#ifndef PHYSICS_MOVEMENT_COMPONENT_H
#define PHYSICS_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "Component.h"
#include "Point.h"
#include "EventCustom.h"
#include "Physics/SynthComponent.h"
#include "Physics/EventListenerCustom.h"

USING_NS_CC;

namespace Physics
{
class MovementComponent : public Component, public SynthComponent
{
protected:
	Point _speed;

	Point _direction;

	Point _acceleration;

	Point _gravity;

	boolean _bStartMoving;

	EventListenerCustom* _pEditMoveEventListener;

	EventListenerCustom* _pJumpEventListener;

	EventListenerCustom* _pInterruptMoveEventListener;

public:
	static char* COMPONENT_TYPE;


protected:
	/**
	 *
	 */
	MovementComponent();

	virtual bool init();

	virtual void initListeners();

	void onEditMove(EventCustom* pEvent);

	void onJump(EventCustom* pEvent);

	void onInterruptMove(EventCustom* pEvent);

	/**
	 *
	 */
	void update(float fDt);

public:
	/**
	 *
	 */
	~MovementComponent();

	static MovementComponent* create(Point acceleration, Point gravity);

	Point getSpeed();

	Point getDirection();

	Point getAcceleration();

	Point getGravity();

	void setSpeed(Point speed);

	/**
	 *
	 */
	void setDirection(Point direction);

	void setAcceleration(Point acceleration);

	void setGravity(Point gravity);

	bool isStarting();

};

}  // namespace Physics
#endif
