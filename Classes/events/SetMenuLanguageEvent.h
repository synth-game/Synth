#ifndef EVENTS_MENUEVENTS_SET_MENU_LANGUAGE_EVENT_H
#define EVENTS_MENUEVENTS_SET_MENU_LANGUAGE_EVENT_H

#include "Events/MenuEvents/SetLanguageEvent.h"

namespace events
{
namespace MenuEvents
{
class SetMenuLanguageEvent : public SetLanguageEvent
{
public:
	static char* sEventName;


public:
	SetMenuLanguageEvent();

	/**
	 *
	 */
	~SetMenuLanguageEvent();

};

}  // namespace MenuEvents
}  // namespace events
#endif
