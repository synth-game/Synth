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

	/*! \brief Initialize the component thanks to its COMPONENT_TYPE
	 * \return true
	 */
	bool init();

	/*! \brief Create the component
	 * \param position The position of the actor.
	 * \param size The size of the actor.
	 * \param fRotationAngle The rotation angle of the actor.
	 * \param anchorPoint The anchor point of the actor.
	 * \return GeometryComponent*
	 */
	static GeometryComponent* create(Point position, Size size, float fRotationAngle, Point anchorPoint);

	inline Point getPosition() { return _position; };

	inline Size getSize() { return _size; };

	inline float getRotationAngle() { return _fRotationAngle; };

	inline Point getAnchorPoint() { return _anchorPoint; };

	inline void setPosition(Point position) { _position = position; };

	inline void setSize(Size size) { _size = size; };

	inline void setRotationAngle(float fRotationAngle) { _fRotationAngle = fRotationAngle; };

	inline void setAnchorPoint(Point anchorPoint) { _anchorPoint = anchorPoint; };

	/*
	 * Members
	 */

	/*! \brief The identifier of the component. */
	static const char* COMPONENT_TYPE;

protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	GeometryComponent();

	/*! \brief Initialize the listeners
	 * \return void
	 */
	void initListeners();

	/*! \brief Method called when a ChangePositionEvent is catched
	 * \param pEvent the event catched
	 * \return void
	 */
	void onChangePosition(EventCustom* pEvent);

	/*
	 * Members
	 */

	/*! \brief The position (x,y) of the actor. (0,0) is at the bottom left of the scene */
	Point _position;

	/*! \brief The size (w,h) of the actor. Used to determine the future bounding box of the actor. */
	Size _size;

	/*! \brief The rotation angle of the actor. Rotation is done towards the left. */
	float _fRotationAngle;

	/*! \brief The anchor point of the actor. The rotation is done around this point. (0,0) is at the bottom left of the actor. */
	Point _anchorPoint;

private:
	/*
	 * Members
	 */

	/*! \brief ChangePositionEvent listener. */
	EventListenerCustom* _pChangePositionListener;


};

}  // namespace physics
#endif
