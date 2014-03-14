/*!
 * \file MovementComponent.h
 * \brief Main manager, the entry point of our program
 * \author Flora Jullien
 * \date 12/02/2014
 */
#ifndef PHYSICS_MOVEMENT_COMPONENT_H
#define PHYSICS_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "core/SynthComponent.h"
#include "core/ActorState.h"
#include "physics/GeometryComponent.h"

USING_NS_CC;

namespace physics {

/*! \class MovementComponent */
class MovementComponent : public core::SynthComponent {

public:
	/*! \brief Destructor */
	~MovementComponent();

	static MovementComponent* create(Point acceleration, Point gravity, float lowGravityFactor, float highGravityFactor);

	inline Point getSpeed() { return _speed; }
	inline Point getDirection() { return _direction; }
	inline Point getAcceleration() { return _acceleration; }
	inline Point getGravity() { return _gravity; }
	inline Point getBasicGravity() { return _basicGravity; }
	inline float getLowGravityFactor() { return _lowGravityFactor; }
	inline float getHighGravityFactor() { return _highGravityFactor; }
	inline bool isStarting() { return _bStartMoving; }
	inline void setSpeed(Point speed) { _speed = speed; }
	inline void setDirection(Point direction) { _direction = direction; }
	inline void setAcceleration(Point acceleration) { _acceleration = acceleration; }
	inline void setGravity(Point gravity) { _gravity = gravity; }
	inline void setBasicGravity(Point gravity) { _basicGravity = gravity;}
    inline bool isLateralMoving() { return _bIsLateralMoving; };

	static const char* COMPONENT_TYPE;

protected:
	/*! \brief Constructor */
	MovementComponent();

	virtual bool init();
	virtual void initListeners();

	void onEditMove(EventCustom* pEvent);
	void onJump(EventCustom* pEvent);
	void onInterruptMove(EventCustom* pEvent);
	void onChangeState(EventCustom* pEvent);
	void update(float fDt);
    Point computeNextPosition();

	Point _speed;
	Point _direction;
	Point _acceleration;
    Point _previousNextPositionComputed;
    bool _bIsLateralMoving;
	Point _basicGravity;
	Point _gravity; //current value of the gravity
	float _lowGravityFactor;
	float _highGravityFactor;
	bool _bStartMoving;
	core::ActorState _eMovingState;

	EventListenerCustom* _pEditMoveEventListener;
	EventListenerCustom* _pJumpEventListener;
	EventListenerCustom* _pInterruptMoveEventListener;
	EventListenerCustom* _pChangeStateEventListener;
};

}  // namespace physics
#endif
