#ifndef EVENTS_GAMEEVENTS_ENTER_LIGHT_EVENT_H
#define EVENTS_GAMEEVENTS_ENTER_LIGHT_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class EnterLightEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	EnterLightEvent();

	/**
	 *
	 */
	~EnterLightEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
