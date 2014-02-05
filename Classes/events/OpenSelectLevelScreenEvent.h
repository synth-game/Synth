#ifndef EVENTS_SCREENEVENTS_OPEN_SELECT_LEVEL_SCREEN_EVENT_H
#define EVENTS_SCREENEVENTS_OPEN_SELECT_LEVEL_SCREEN_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace ScreenEvents
{
class OpenSelectLevelScreenEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	OpenSelectLevelScreenEvent();

	/**
	 *
	 */
	~OpenSelectLevelScreenEvent();

};

}  // namespace ScreenEvents
}  // namespace events
#endif
