#ifndef EVENTS_MENUEVENTS_EXIT_GAME_EVENT_H
#define EVENTS_MENUEVENTS_EXIT_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace MenuEvents
{
class ExitGameEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	ExitGameEvent();

	/**
	 *  
	 */
	~ExitGameEvent();

};

}  // namespace MenuEvents
}  // namespace Events
#endif
