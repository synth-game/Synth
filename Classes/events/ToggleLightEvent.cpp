#include "ToggleLightEvent.h"

namespace events 
{
const char* ToggleLightEvent::EVENT_NAME = "ToggleLightEvent";

ToggleLightEvent::ToggleLightEvent() {
}

ToggleLightEvent::~ ToggleLightEvent() {
}

bool ToggleLightEvent::isOn() {
	return 0;
}

void ToggleLightEvent::setOn(bool bOn) {
}
}  // namespace events
