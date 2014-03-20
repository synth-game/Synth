/*!
 * \file ResumeGameEvent.cpp
 * \brief Resume the game
 * \author Chupee
 * \date 20/03/2014
 */
#include "ResumeGameEvent.h"

namespace events {

const char* ResumeGameEvent::EVENT_NAME = "ResumeGameEvent";

ResumeGameEvent::ResumeGameEvent() :
	SynthEvent(nullptr, EVENT_NAME) {
}

ResumeGameEvent::~ResumeGameEvent() {
}

}  // namespace events
