#include "ToggleLightEvent.h"

namespace events
{
namespace GameEvents
{
char* ToggleLightevent::sEventName;

ToggleLightevent::ToggleLightEvent()
{
}

ToggleLightevent::~ ToggleLightEvent()
{
}

bool ToggleLightevent::isOn()
{
	return 0;
}

void ToggleLightevent::setOn(bool bOn)
{
}
}  // namespace GameEvents
}  // namespace events
