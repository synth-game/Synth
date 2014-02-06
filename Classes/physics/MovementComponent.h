#ifndef PHYSICS_MOVEMENT_COMPONENT_H
#define PHYSICS_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "core/SynthComponent.h"


USING_NS_CC;

namespace physics
{
class MovementComponent : public core::SynthComponent
{
protected:
	Point _speed;

	Point _direction;

	Point _acceleration;

	Point _gravity;

	bool _bStartMoving;

	EventListenerCustom* _pEditMoveEventListener;

	EventListenerCustom* _pJumpEventListener;

	EventListenerCustom* _pInterruptMoveEventListener;

public:
	static const char* COMPONENT_TYPE;


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

}  // namespace physics
#endif
