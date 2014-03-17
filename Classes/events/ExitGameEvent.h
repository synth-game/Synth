#ifndef EVENTS_MENUEVENTS_EXIT_GAME_EVENT_H
#define EVENTS_MENUEVENTS_EXIT_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class ExitGameEvent : public events::SynthEvent {
public:
	static const char* EVENT_NAME;

public:
	ExitGameEvent();

	~ExitGameEvent();

};

}  // namespace events
#endif
