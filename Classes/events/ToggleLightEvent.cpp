#include "ToggleLightEvent.h"

namespace events
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
}  // namespace events
