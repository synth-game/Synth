#ifndef EVENTS_GAMEEVENTS_START_SOUND_EVENT_H
#define EVENTS_GAMEEVENTS_START_SOUND_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class StartSoundEvent : public events::SynthEvent
{
public:
	static char* sEventName;


public:
	StartSoundEvent();

	/**
	 *
	 */
	~StartSoundEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
