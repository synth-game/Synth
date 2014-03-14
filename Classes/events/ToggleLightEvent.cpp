/*!
 * \file ToggleLightEvent.cpp
 * \brief Event that turns on/off a light
 * \author Chupee
 * \date 26/02/2014
 */
#include "ToggleLightEvent.h"

namespace events {

const char* ToggleLightEvent::EVENT_NAME = "ToggleLightEvent";

ToggleLightEvent::ToggleLightEvent(Node* pSource, core::SynthActor* pTarget, bool bOn) :
	 SynthEvent(pSource, EVENT_NAME),
	_bOn(bOn),
	_pTarget(pTarget) {
}

ToggleLightEvent::~ ToggleLightEvent() {
}

}  // namespace events
