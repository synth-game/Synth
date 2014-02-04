#ifndef EVENTS_MENUEVENTS_SET_MUSIC_VOLUME_EVENT_H
#define EVENTS_MENUEVENTS_SET_MUSIC_VOLUME_EVENT_H

#include "Events/MenuEvents/SetBoundedParamEvent.h"

namespace Events
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
}  // namespace Events
#endif
