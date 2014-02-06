#ifndef EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H
#define EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class ToggleLightEvent : public events::SynthEvent
{
private:
	bool bOn;

public:
	static char* sEventName;


public:
	ToggleLightEvent();

	/**
	 *
	 */
	~ ToggleLightEvent();

	bool isOn();

	void setOn(bool bOn);

};

}  // namespace GameEvents
}  // namespace events
#endif