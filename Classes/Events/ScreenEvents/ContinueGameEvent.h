#ifndef EVENTS_SCREENEVENTS_CONTINUE_GAME_EVENT_H
#define EVENTS_SCREENEVENTS_CONTINUE_GAME_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace ScreenEvents
{
class ContinueGameEvent : public Events::SynthEvent
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
}  // namespace Events
#endif
