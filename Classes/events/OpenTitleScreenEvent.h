#ifndef EVENTS_SCREENEVENTS_OPEN_TITLE_SCREEN_EVENT_H
#define EVENTS_SCREENEVENTS_OPEN_TITLE_SCREEN_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace ScreenEvents
{
class OpenTitleScreenEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	OpenTitleScreenEvent();

	/**
	 *
	 */
	~OpenTitleScreenEvent();

};

}  // namespace ScreenEvents
}  // namespace events
#endif
