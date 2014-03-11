/*!
 * \file LightCollision.h
 * \brief Manage collision with the lights cone
 * \author Jijidici
 * \date 11/03/2014
 */
#ifndef PHYSICS_LIGHT_COLLISION_H
#define PHYSICS_LIGHT_COLLISION_H

#include <vector>
#include "cocos2d.h"
#include "core/SynthActor.h"
#include "game/LightMap.h"

USING_NS_CC;

namespace physics {
/*!
 * \class LightCollision
 * \brief Manage collision with the level bitmask
 */
class LightCollision {
public:
	/*! \brief Constructor */
	LightCollision(std::vector<core::SynthActor*> lightCollection, game::LightMap* pLightMap);
	/*! \brief Destructor */
	~LightCollision();

	Color4B getCurrentColor(Point actorPos);

protected:
	std::vector<core::SynthActor*> _lightCollection;
	game::LightMap* _pLightMap;
	Color4B _currentColor;
};

}  // namespace physics
#endif
