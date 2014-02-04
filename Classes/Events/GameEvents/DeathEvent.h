#ifndef EVENTS_GAMEEVENTS_DEATH_EVENT_H
#define EVENTS_GAMEEVENTS_DEATH_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class DeathEvent : public Events::SynthEvent
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
}  // namespace Events
#endif
