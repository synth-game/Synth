/*!
 * \file LightCollision.h
 * \brief Manage collision with the lights cone
 * \author Jijidici
 * \date 11/03/2014
 */
#include "LightCollision.h"

namespace physics {

LightCollision::LightCollision(std::vector<core::SynthActor*> lightCollection, game::LightMap* pLightMap) 
	: _lightCollection(lightCollection)
	, _pLightMap(pLightMap) {
	_pLightMap->updateLighting(_lightCollection);
}

LightCollision::~LightCollision() {

}

}  // namespace physics
