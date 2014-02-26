#ifndef EVENTS_SCREENEVENTS_OPEN_SETTINGS_EVENT_H
#define EVENTS_SCREENEVENTS_OPEN_SETTINGS_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace ScreenEvents
{
class OpenSettingsEvent : public events::SynthEvent
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
}  // namespace events
#endif
