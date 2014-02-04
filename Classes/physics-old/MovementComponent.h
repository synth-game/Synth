/* *****************************************************
 *		MovementComponent.h - @ Jeremie Defaye - 02/02/14
 ***************************************************** */

#ifndef __MOVEMENT_COMPONENT_H__
#define __MOVEMENT_COMPONENT_H__

#include "cocos2d.h"
#include "core/SynthComponent.h"

USING_NS_CC;

class MovementComponent : public SynthComponent {

public:
	~MovementComponent();
	virtual bool init();
	static MovementComponent* create(Point gravity);

	inline Point getSpeed() { return _speed; }
	inline Point getGravity() { return _gravity; }
	inline void setSpeed(Point speed) { _speed = speed; }
	inline void setGravity(Point gravity) { _gravity = gravity; }

	static const char* COMPONENT_TYPE;

protected:
	MovementComponent();
	virtual void initListeners();
	virtual void update(float fDt);
	
	Point _speed;
	Point _gravity;

};

#endif // __MOVEMENT_COMPONENT_H__