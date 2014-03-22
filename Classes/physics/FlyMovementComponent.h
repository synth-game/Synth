/*!
 * \file MovementComponent.h
 * \brief The girl flies !
 * \author Tom Duchêne
 * \date 12/02/2014
 */

#ifndef PHYSICS_FLY_MOVEMENT_COMPONENT_H
#define PHYSICS_FLY_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "Physics/MovementComponent.h"
#include "core/SynthActor.h"

USING_NS_CC;

namespace physics
{
/*! \class MovementComponent */
class FlyMovementComponent : public MovementComponent {

public:
	/*! \brief Destructor */
	~FlyMovementComponent();

	static FlyMovementComponent* create(Point acceleration);

protected:
	/*! \brief Constructor */
	FlyMovementComponent();

	/**
	 * Make normal movment sur l'axe y
	 */
	void onEditMove(EventCustom* pEvent);

	/**
	 * Disable jump
	 */
	void onJump(EventCustom* pEvent);

	/**
	 *
	 */
	virtual void update(float fDt) override;



};

}  // namespace physics
#endif
