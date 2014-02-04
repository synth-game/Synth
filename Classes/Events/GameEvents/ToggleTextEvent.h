#ifndef EVENTS_GAMEEVENTS_TOGGLE_TEXT_EVENT_H
#define EVENTS_GAMEEVENTS_TOGGLE_TEXT_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class ToggleTextEvent : public Events::SynthEvent
{
private:
	boolean bOn;

	char* _sVoiceTag;

public:
	static char* sEventName;


public:
	ToggleTextEvent();

	~ToggleTextEvent();

	void setVoiceTag(char* sVoiceTag);

	char* getVoiceTag();

	boolean isOn();

	void setOn(boolean bOn);

};

}  // namespace GameEvents
}  // namespace Events
#endif
