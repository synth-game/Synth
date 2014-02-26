#ifndef EVENTS_SCREENEVENTS_NEW_GAME_EVENT_H
#define EVENTS_SCREENEVENTS_NEW_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace ScreenEvents
{
class NewGameEvent : public events::SynthEvent
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
}  // namespace events
#endif
