#ifndef PHYSICS_STICK_COLLISION_COMPONENT_H
#define PHYSICS_STICK_COLLISION_COMPONENT_H


#include "Physics/CollisionComponent.h"

namespace physics
{
class StickCollisionComponent : public CollisionComponent
{
private:
	bool _bIsSticked;

protected:
    
    /*! \brief Constructor */
	StickCollisionComponent();
    ECollisionType boundingTest(events::TestCollisionEvent* pInitiatorEvent, Point& resPosition);
    bool init();
	void initListeners();
    
    /**
	 * Si un des points cardinaux collisionne -> faire le test de pente contre la surface correspondante
	 *
	 */
	void onTestCollision(EventCustom* pEvent);
    
public:
    
    void onEnter();
    
    /*! \brief Destructor */
	~StickCollisionComponent();
    
    static StickCollisionComponent* create();
    
    void update(float fDt);

};

}  // namespace physics
#endif
