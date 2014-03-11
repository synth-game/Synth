/*!
 * \file EnterLightEvent.h
 * \brief Event to signal the source change color lighting
 * \author Jijidici
 * \date 11/03/2014
 */
#include "EnterLightEvent.h"

namespace events {

const char* EnterLightEvent::EVENT_NAME = "EnterLightEvent";

EnterLightEvent::EnterLightEvent(Node* pSource, Color4B lightingColor) 
	: SynthEvent(pSource, EVENT_NAME)
	, _lightingColor(lightingColor) {

}

EnterLightEvent::~EnterLightEvent() {

}

}  // namespace events
