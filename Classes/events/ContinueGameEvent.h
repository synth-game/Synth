#ifndef EVENTS_SCREENEVENTS_CONTINUE_GAME_EVENT_H
#define EVENTS_SCREENEVENTS_CONTINUE_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace ScreenEvents
{
class ContinueGameEvent : public events::SynthEvent
{
public:
	static char* sEventName;


public:
	ContinueGameEvent();

	/**
	 *
	 */
	~ContinueGameEvent();

};

}  // namespace ScreenEvents
}  // namespace events
#endif
