#ifndef EVENTS_GAMEEVENTS_TOGGLE_TEXT_EVENT_H
#define EVENTS_GAMEEVENTS_TOGGLE_TEXT_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class ToggleTextEvent : public Events::SynthEvent
{
private:
	bool bOn;

	char* _sVoiceTag;

public:
	static char* sEventName;


public:
	ToggleTextEvent();

	~ToggleTextEvent();

	void setVoiceTag(char* sVoiceTag);

	char* getVoiceTag();

	bool isOn();

	void setOn(bool bOn);

};

}  // namespace GameEvents
}  // namespace events
#endif
