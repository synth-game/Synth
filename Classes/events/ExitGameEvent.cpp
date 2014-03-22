#include "ExitGameEvent.h"

namespace events {
const char* ExitGameEvent::EVENT_NAME = "ExitGameEvent";

ExitGameEvent::ExitGameEvent() :
	SynthEvent(nullptr, EVENT_NAME) {
}

ExitGameEvent::~ExitGameEvent() {
}

}  // namespace events
