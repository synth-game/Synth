/*!
 * \file GeometryComponent.h
 * \brief Class giving a position, a size, a rotation angle and an anchorpoint to the SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#ifndef PHYSICS_GEOMETRY_COMPONENT_H
#define PHYSICS_GEOMETRY_COMPONENT_H

#include "cocos2d.h"
#include "Core/SynthComponent.h"

USING_NS_CC;

namespace physics {

/*! \class GeometryComponent
 * \brief Class giving a position, a size, a rotation angle and an anchorpoint to the SynthActor.
 *
 * It has to be called before a MovementComponent or a SpriteComponent, etc. (they need a GeometryComponent).
 */
class GeometryComponent : public core::SynthComponent {

public:
	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~GeometryComponent();

	virtual bool init() = 0;

	static GeometryComponent* create(Point position, Size size, float fRotationAngle, Point anchorPoint);

	Point getPosition();

	Size getSize();

	float getRotationAngle();

	Point getAnchorPoint();

	void setPosition(Point position);

	void setSize(Size size);

	void setRotationAngle(float fRotationAngle);

	void setAnchorPoint(Point anchorPoint);

	/*
	 * Members
	 */

	static const char* COMPONENT_TYPE;

protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	GeometryComponent();

	void initListeners();

	void onChangePosition(EventCustom* pEvent);

	/*
	 * Members
	 */

	Point _position;

	Size _size;

	float _fRotationAngle;

	Point _anchorPoint;

private:
	/*
	 * Members
	 */

	EventListenerCustom* _pChangePositionListener;


};

}  // namespace physics
#endif
