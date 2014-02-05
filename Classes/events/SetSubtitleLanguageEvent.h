#ifndef EVENTS_MENUEVENTS_SET_SUBTITLE_LANGUAGE_EVENT_H
#define EVENTS_MENUEVENTS_SET_SUBTITLE_LANGUAGE_EVENT_H

#include "Events/SetLanguageEvent.h"

namespace events
{
namespace MenuEvents
{
class SetSubtitleLanguageEvent : public SetLanguageEvent
{
public:
	static char* sEventName;


public:
	SetSubtitleLanguageEvent();

	/**
	 *
	 */
	~SetSubtitleLanguageEvent();

};

}  // namespace MenuEvents
}  // namespace events
#endif
