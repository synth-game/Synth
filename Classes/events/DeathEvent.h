#ifndef EVENTS_GAMEEVENTS_DEATH_EVENT_H
#define EVENTS_GAMEEVENTS_DEATH_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class DeathEvent : public events::SynthEvent
{
public:
	static char* sEventName;


public:
	DeathEvent();

	/**
	 *
	 */
	~DeathEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
