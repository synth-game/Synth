#ifndef EVENTS_GAMEEVENTS_WIN_EVENT_H
#define EVENTS_GAMEEVENTS_WIN_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class WinEvent : public events::SynthEvent
{
public:
	static const char* EVENT_NAME;


public:
	WinEvent();

	~WinEvent();

};

}  // namespace events
#endif
