/* *****************************************************
 *		GeometryComponent.h - @ Flora Jullien - 30/01/14
 ***************************************************** */

#ifndef PHYSICS_GEOMETRY_COMPONENT_H
#define PHYSICS_GEOMETRY_COMPONENT_H

#include "cocos2d.h"
#include "Component.h"
#include "Point.h"
#include "Size.h"
#include "EventCustom.h"
#include "Physics/SynthComponent.h"
#include "Physics/EventListenerCustom.h"
#include "Core/SynthComponent.h"

USING_NS_CC;

namespace Physics
{
class GeometryComponent : public Component, public SynthComponent, public core::SynthComponent
{
private:
	EventListenerCustom* _pChangePositionListener;


protected:
	Point _position;

	Size _size;

	float _fRotationAngle;

	Point _anchorPoint;


public:
	static char* COMPONENT_TYPE;


protected:
	/**
	 *
	 */
	GeometryComponent();

	void initListeners();

	void onChangePosition(EventCustom* pEvent);

public:
	~GeometryComponent();

	virtual bool init()=0;

	static GeometryComponent* create(Point position, Size size, float fRotationAngle, Point anchorPoint);

	Point getPosition();

	Size getSize();

	float getRotationAngle();

	Point getAnchorPoint();

	void setPosition(Point position);

	void setSize(Size size);

	void setRotationAngle(float fRotationAngle);

	void setAnchorPoint(Point anchorPoint);

};

}  // namespace Physics
#endif
