#ifndef EVENTS_SCREENEVENTS_NEW_GAME_EVENT_H
#define EVENTS_SCREENEVENTS_NEW_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace ScreenEvents
{
class NewGameEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	NewGameEvent();

	/**
	 *  
	 */
	~NewGameEvent();

};

}  // namespace ScreenEvents
}  // namespace Events
#endif
