/*!
 * \file CollisionComponent.h
 * \brief Allow and compute collisions
 * \author Jijidici
 * \date 20/02/2014
 */
#ifndef PHYSICS_COLLISION_COMPONENT_H
#define PHYSICS_COLLISION_COMPONENT_H

#include "cocos2d.h"
#include "core/SynthComponent.h"
#include "physics/PhysicCollision.h"
#include "physics/LightCollision.h"
#include "events/TestCollisionEvent.h"

USING_NS_CC;

namespace physics {
/*! \class GeometryComponent
 * \brief Allow and compute collisions
 *
 * It is called by a TestCollisionEvent (from MovementComponent)
 */
class CollisionComponent : public core::SynthComponent {
public:
	/*! \brief Destructor */
	~CollisionComponent();

	static CollisionComponent* create();

	void addPhysicCollision(PhysicCollision* pCollision) { _pPhysicCollision = pCollision; }
	void addLightCollision(LightCollision* pCollision) { _pLightCollision = pCollision; }
	PhysicCollision* getPhysicCollision() { return _pPhysicCollision; }
	LightCollision* getLightCollision() { return _pLightCollision; }

	void onTestCollision(EventCustom* pEvent);

	static const char* COMPONENT_TYPE;

protected:
	/*! \brief Constructor */
	CollisionComponent();

	bool init();
	void initListeners();

	bool boundingTest(events::TestCollisionEvent* initiatorEvent, Point& resPosition);

	PhysicCollision* _pPhysicCollision;
	LightCollision* _pLightCollision;

	EventListenerCustom* _pTestCollisionEventListener;
};

}  // namespace physics
#endif
