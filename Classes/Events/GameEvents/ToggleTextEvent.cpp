#include "ToggleTextEvent.h"

namespace events
{
namespace GameEvents
{
char* ToggleTextevent::sEventName;

ToggleTextevent::ToggleTextEvent()
{
}

ToggleTextevent::~ToggleTextEvent()
{
}

void ToggleTextevent::setVoiceTag(char* sVoiceTag)
{
}

char* ToggleTextevent::getVoiceTag()
{
	return 0;
}

bool ToggleTextevent::isOn()
{
	return 0;
}

void ToggleTextevent::setOn(bool bOn)
{
}
}  // namespace GameEvents
}  // namespace events
