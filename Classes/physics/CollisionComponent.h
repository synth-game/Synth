#ifndef PHYSICS_COLLISION_COMPONENT_H
#define PHYSICS_COLLISION_COMPONENT_H


#include "cocos2d.h"
#include "core/SynthComponent.h"
#include "Physics/PhysicCollision.h"
#include "Physics/LightCollision.h"

USING_NS_CC;

namespace physics
{
class CollisionComponent : public core::SynthComponent
{
private:
	Point _absoluteOriginPosition;

	Image* _pBitmask;

	PhysicCollision* _pPhysicCollision;

	LightCollision* _pLightCollision;

	EventListenerCustom* _pTestCollisionEventListener;

public:
	static const char* COMPONENT_TYPE;


protected:
	CollisionComponent();

	bool init();

	void initListeners();

public:
	~CollisionComponent();

	/**
	 *
	 */
	static CollisionComponent* create(Image* bitmask, Point absoluteOriginPosition);

	void addPhysicCollision(PhysicCollision* pCollision);

	void addLightCollision(LightCollision* pCollision);

	/**
	 * Test de collision avec les 4 points cardinaux de l'Actor -> repoussement si collision
	 * Puis test de pente
	 *
	 *
	 */
	void onTestCollision(EventCustom* pEvent);

};

}  // namespace physics
#endif
