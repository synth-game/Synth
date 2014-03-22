/*!
 * \file LightCollision.h
 * \brief Manage collision with the lights cone
 * \author Jijidici
 * \date 11/03/2014
 */
#include "LightCollision.h"
#include "events/EnterLightEvent.h"

namespace physics {

LightCollision::LightCollision(std::vector<core::SynthActor*> lightCollection, game::LightMap* pLightMap) 
	: _lightCollection(lightCollection)
	, _pLightMap(pLightMap) {
	_pLightMap->updateLighting(_lightCollection);
}

LightCollision::~LightCollision() {

}

Color4B LightCollision::getCurrentColor(Point actorPos) {
	Color4B newLightingColor = _pLightMap->getPixelLighting(actorPos);

	if(newLightingColor != _currentColor) {
		events::EnterLightEvent* pEnterLightEvent = new events::EnterLightEvent(nullptr, newLightingColor);
		EventDispatcher::getInstance()->dispatchEvent(pEnterLightEvent);
		delete pEnterLightEvent;
	}

	_currentColor = newLightingColor;
	return _currentColor;
}

bool LightCollision::isInWhiteLight(Point position) {
	bool bRet = false;
	Color4B sampleLightingColor = _pLightMap->getPixelLighting(position);
	if(sampleLightingColor == Color4B::WHITE) {
		bRet = true;
	}

	return bRet;
}

}  // namespace physics
