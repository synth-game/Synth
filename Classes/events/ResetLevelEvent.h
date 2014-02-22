#ifndef EVENTS_GAMEEVENTS_RESET_LEVEL_EVENT_H
#define EVENTS_GAMEEVENTS_RESET_LEVEL_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class ResetLevelEvent : public events::SynthEvent {

public:
	static const char* EVENT_NAME;

public:
	ResetLevelEvent();

	~ResetLevelEvent();

};

}  // namespace events
#endif
