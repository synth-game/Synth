#ifndef EVENTS_MENUEVENTS_SET_SOUND_VOLUMENT_EVENT_H
#define EVENTS_MENUEVENTS_SET_SOUND_VOLUMENT_EVENT_H

#include "Events/SetBoundedParamEvent.h"

namespace events
{
namespace MenuEvents
{
class SetSoundVolumeEvent : public SetBoundedParamEvent
{
public:
	static char* sEventName;


public:
	SetSoundVolumeEvent();

	/**
	 *
	 */
	~SetSoundVolumeEvent();

};

}  // namespace MenuEvents
}  // namespace events
#endif
