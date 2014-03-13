/*!
 * \file DeathEvent.cpp
 * \brief Event detecting when the players dies
 * \author Xopi
 * \date 12/03/2014
 */
#include "DeathEvent.h"

namespace events {

const char* DeathEvent::EVENT_NAME = "DeathEvent";

DeathEvent::DeathEvent()
	: SynthEvent(nullptr, EVENT_NAME) {
}

DeathEvent::~DeathEvent() {
}

}  // namespace events
