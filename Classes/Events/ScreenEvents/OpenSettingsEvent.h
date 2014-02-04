#ifndef EVENTS_SCREENEVENTS_OPEN_SETTINGS_EVENT_H
#define EVENTS_SCREENEVENTS_OPEN_SETTINGS_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace ScreenEvents
{
class OpenSettingsEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	OpenSettingsEvent();

	/**
	 *  
	 */
	~OpenSettingsEvent();

};

}  // namespace ScreenEvents
}  // namespace Events
#endif
