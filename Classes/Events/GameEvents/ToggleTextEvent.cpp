#include "ToggleTextEvent.h"

namespace Events
{
namespace GameEvents
{
char* ToggleTextEvent::sEventName;

ToggleTextEvent::ToggleTextEvent()
{
}

ToggleTextEvent::~ToggleTextEvent()
{
}

void ToggleTextEvent::setVoiceTag(char* sVoiceTag)
{
}

char* ToggleTextEvent::getVoiceTag()
{
	return 0;
}

bool ToggleTextEvent::isOn()
{
	return 0;
}

void ToggleTextEvent::setOn(bool bOn)
{
}
}  // namespace GameEvents
}  // namespace Events
