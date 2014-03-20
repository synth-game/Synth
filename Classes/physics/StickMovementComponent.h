/*!
 * \file StickMovementComponent
 * \brief StickMovement component, actor with this MovementComponent is sticked to the surfaces
 * \author Pierre Criulanscy
 * \date 20/03/2014
 */
#ifndef PHYSICS_STICK_MOVEMENT_COMPONENT_H
#define PHYSICS_STICK_MOVEMENT_COMPONENT_H

#include "cocos2d.h"
#include "physics/MovementComponent.h"
#include "core/SynthActor.h"

USING_NS_CC;

namespace physics
{
class StickMovementComponent : public MovementComponent
{
protected:
    
    enum EDirection {
        LEFT,
        RIGHT,
        TOP,
        BOTTOM
    };
    
    EDirection _eCurrentDirection = BOTTOM;
    
    /*! \brief Constructor */
	StickMovementComponent();
    
    bool _bIsSticked = false;
    bool _bIsJumping = false;
    
	void onEditMove(EventCustom* pEvent);
    void onJump(EventCustom* pEvent);
    void onChangeState(EventCustom* pEvent);
    void onInterruptMove(EventCustom* pEvent);
    void onCollisionEvent(EventCustom* pEvent);
    void onChangePosition(EventCustom* pEvent);

	void update(float fDt);

public:
    /*! \brief Destructor */
	~StickMovementComponent();
    
	static StickMovementComponent* create(Point acceleration, Point gravity);
    
	bool init();
    
    void initListeners();
    
    void onEnter();
    
    EventListenerCustom* _pEditMoveEventListener;
	EventListenerCustom* _pJumpEventListener;
	EventListenerCustom* _pInterruptMoveEventListener;
	EventListenerCustom* _pChangeStateEventListener;

};

}  // namespace physics
#endif
