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
	bool _bTriggeredVoice;

public:
	static char* sEventName;


public:
	VoiceEvent();

	/**
	 *
	 */
	~VoiceEvent();

	bool isTriggeredVoice();

	void setTriggeredVoice(bool bIsTriggeredVoice);

};

}  // namespace GameEvents
}  // namespace Events
#endif
