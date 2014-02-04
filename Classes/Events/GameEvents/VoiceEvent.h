#ifndef EVENTS_GAMEEVENTS_VOICE_EVENT_H
#define EVENTS_GAMEEVENTS_VOICE_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class VoiceEvent : public Events::SynthEvent
{
private:
	boolean _bTriggeredVoice;

public:
	static char* sEventName;


public:
	VoiceEvent();

	/**
	 *  
	 */
	~VoiceEvent();

	boolean isTriggeredVoice();

	void setTriggeredVoice(boolean bIsTriggeredVoice);

};

}  // namespace GameEvents
}  // namespace Events
#endif
