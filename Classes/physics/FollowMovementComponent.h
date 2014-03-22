/*!
 * \file FollowMovementComponent.h
 * \brief The actor follows a target
 * \author Chupee
 * \date 27/02/2014
 */
#ifndef PHYSICS_FOLLOW_MOVEMENT_COMPONENT_H
#define PHYSICS_FOLLOW_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "Physics/MovementComponent.h"
#include "core/SynthActor.h"

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
	/*! \brief Destructor */
	~FollowMovementComponent();

	static FollowMovementComponent* create(Point acceleration, core::SynthActor* target);
	bool init();

	inline core::SynthActor* getTarget() { return _target; }
	void setTarget( core::SynthActor* target );

protected:

	/*
	 * Methods
	 */

	/*! \brief Constructor */
	FollowMovementComponent();

	void initListeners();

	/*! \brief  */
	void onChangeTarget(EventCustom* pEvent);

	/**
	 * Make the movment toward the target position
	 */
	void update(float fDt);


	/*
	 * Members
	 */

	/*! \brief  */
	EventListenerCustom* _pChangeTargetEventListener;

	core::SynthActor* _target;



};

}  // namespace physics
#endif
