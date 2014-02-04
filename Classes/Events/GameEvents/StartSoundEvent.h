#ifndef EVENTS_GAMEEVENTS_START_SOUND_EVENT_H
#define EVENTS_GAMEEVENTS_START_SOUND_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class StartSoundEvent : public Events::SynthEvent
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
}  // namespace Events
#endif
