#ifndef EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H
#define EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class ToggleLightEvent : public events::SynthEvent {

private:
	bool bOn;

public:
	static const char* EVENT_NAME;

public:
	ToggleLightEvent();

	~ ToggleLightEvent();

	bool isOn();

	void setOn(bool bOn);

};

}  // namespace events
#endif
