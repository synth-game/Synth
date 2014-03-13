/*!
 * \file ResetLevelEvent.cpp
 * \brief Event detecting when the level has to reset
 * \author Xopi
 * \date 13/03/2014
 */
#include "ResetLevelEvent.h"

namespace events {

const char* ResetLevelEvent::EVENT_NAME = "ResetLevelEvent";

ResetLevelEvent::ResetLevelEvent()
	: SynthEvent(nullptr, EVENT_NAME) {
}

ResetLevelEvent::~ResetLevelEvent() {
}

}  // namespace events
