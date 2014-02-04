#include "CollisionComponent.h"

namespace Physics
{

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

CollisionComponent* CollisionComponent::create(Image* bitmask, Point absoluteOriginPosition)
{
	return 0;
}

void CollisionComponent::addPhysicCollision(PhysicCollision* pCollision)
{
}

void CollisionComponent::addLightCollision(LightCollision* pCollision)
{
}

void CollisionComponent::onTestCollision(EventCustom* pEvent)
{
}

boolean CollisionComponent::init()
{
	return 0;
}

void CollisionComponent::initListeners()
{
}
}  // namespace Physics
