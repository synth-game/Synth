#include "NewGameEvent.h"

namespace events {

const char* NewGameEvent::EVENT_NAME = "NewGameEvent";

NewGameEvent::NewGameEvent() :
	SynthEvent(nullptr, EVENT_NAME) {
}

NewGameEvent::~NewGameEvent() {
}
}  // namespace events
