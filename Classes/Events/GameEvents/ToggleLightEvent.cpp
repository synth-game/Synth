#include "ToggleLightEvent.h"

namespace Events
{
namespace GameEvents
{
char* ToggleLightEvent::sEventName;

ToggleLightEvent::ToggleLightEvent()
{
}

ToggleLightEvent::~ ToggleLightEvent()
{
}

bool ToggleLightEvent::isOn()
{
	return 0;
}

void ToggleLightEvent::setOn(bool bOn)
{
}
}  // namespace GameEvents
}  // namespace Events
