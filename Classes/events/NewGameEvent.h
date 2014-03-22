#ifndef EVENTS_SCREENEVENTS_NEW_GAME_EVENT_H
#define EVENTS_SCREENEVENTS_NEW_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class NewGameEvent : public events::SynthEvent {
public:
	static const char* EVENT_NAME;

public:
	NewGameEvent();

	~NewGameEvent();

};

}  // namespace events
#endif
