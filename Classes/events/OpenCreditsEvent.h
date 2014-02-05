#ifndef EVENTS_SCREENEVENTS_OPEN_CREDITS_EVENT_H
#define EVENTS_SCREENEVENTS_OPEN_CREDITS_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace ScreenEvents
{
class OpenCreditsEvent : public events::SynthEvent
{
public:
	static char* sEventName;


public:
	OpenCreditsEvent();

	/**
	 *
	 */
	~OpenCreditsEvent();

};

}  // namespace ScreenEvents
}  // namespace events
#endif
