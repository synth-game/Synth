/*!
 * \file ResumeGameEvent.h
 * \brief Resume the game
 * \author Chupee
 * \date 20/03/2014
 */
#ifndef EVENTS_GAMEEVENTS_RESUME_GAME_EVENT_H
#define EVENTS_GAMEEVENTS_RESUME_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class ResumeGameEvent : public events::SynthEvent {

public:
	static const char* EVENT_NAME;

public:
	ResumeGameEvent();

	~ResumeGameEvent();

};

}  // namespace events
#endif
