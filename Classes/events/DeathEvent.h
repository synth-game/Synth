#ifndef EVENTS_GAMEEVENTS_DEATH_EVENT_H
#define EVENTS_GAMEEVENTS_DEATH_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class DeathEvent : public events::SynthEvent {
public:
	static const char* EVENT_NAME;


public:
	DeathEvent();

	~DeathEvent();

};

}  // namespace events
#endif
