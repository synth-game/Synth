#ifndef EVENTS_MENUEVENTS_SET_SUBTITLE_LANGUAGE_EVENT_H
#define EVENTS_MENUEVENTS_SET_SUBTITLE_LANGUAGE_EVENT_H

#include "Events/MenuEvents/SetLanguageEvent.h"

namespace Events
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
}  // namespace Events
#endif
