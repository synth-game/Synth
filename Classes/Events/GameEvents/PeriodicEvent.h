#ifndef EVENTS_GAMEEVENTS_PERIODIC_EVENT_H
#define EVENTS_GAMEEVENTS_PERIODIC_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class PeriodicEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	PeriodicEvent();

	/**
	 *
	 */
	~PeriodicEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
