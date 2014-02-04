#ifndef EVENTS_GAMEEVENTS_RESUME_GAME_EVENT_H
#define EVENTS_GAMEEVENTS_RESUME_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class ResumeGameEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	ResumeGameEvent();

	/**
	 *  
	 */
	~ResumeGameEvent();

};

}  // namespace GameEvents
}  // namespace Events
#endif
