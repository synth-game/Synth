#ifndef EVENTS_MENUEVENTS_SET_MUSIC_VOLUME_EVENT_H
#define EVENTS_MENUEVENTS_SET_MUSIC_VOLUME_EVENT_H

#include "Events/SetBoundedParamEvent.h"

namespace events
{
namespace MenuEvents
{
class SetMusicVolumeEvent : public SetBoundedParamEvent
{
public:
	static char* sEventName;


public:
	SetMusicVolumeEvent();

	/**
	 *
	 */
	~SetMusicVolumeEvent();

};

}  // namespace MenuEvents
}  // namespace events
#endif
