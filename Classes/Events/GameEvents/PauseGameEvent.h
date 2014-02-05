#ifndef EVENTS_GAMEEVENTS_PAUSE_GAME_EVENT_H
#define EVENTS_GAMEEVENTS_PAUSE_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class PauseGameEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	PauseGameEvent();

	/**
	 *
	 */
	~PauseGameEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
