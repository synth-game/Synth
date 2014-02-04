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

boolean ToggleLightEvent::isOn()
{
	return 0;
}

void ToggleLightEvent::setOn(boolean bOn)
{
}
}  // namespace GameEvents
}  // namespace Events
