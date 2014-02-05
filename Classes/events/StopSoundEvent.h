#ifndef EVENTS_GAMEEVENTS_STOP_SOUND_EVENT_H
#define EVENTS_GAMEEVENTS_STOP_SOUND_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class StopSoundEvent : public events::SynthEvent
{
public:
	static char* sEventName;


public:
	StopSoundEvent();

	/**
	 *
	 */
	~StopSoundEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
