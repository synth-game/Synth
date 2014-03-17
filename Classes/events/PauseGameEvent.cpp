#include "PauseGameEvent.h"

namespace events {

const char* PauseGameEvent::EVENT_NAME = "PauseGameEvent";

PauseGameEvent::PauseGameEvent() :
	SynthEvent(nullptr, EVENT_NAME) {
}

PauseGameEvent::~PauseGameEvent() {
}

}  // namespace events
