#ifndef EVENTS_GAMEEVENTS_PAUSE_GAME_EVENT_H
#define EVENTS_GAMEEVENTS_PAUSE_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class PauseGameEvent : public events::SynthEvent {
public:
	static const char* EVENT_NAME;

public:
	PauseGameEvent();

	~PauseGameEvent();

};

}  // namespace events
#endif
