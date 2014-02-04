#ifndef EVENTS_GAMEEVENTS_RESET_LEVEL_EVENT_H
#define EVENTS_GAMEEVENTS_RESET_LEVEL_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class ResetLevelEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	ResetLevelEvent();

	/**
	 *  
	 */
	~ResetLevelEvent();

};

}  // namespace GameEvents
}  // namespace Events
#endif