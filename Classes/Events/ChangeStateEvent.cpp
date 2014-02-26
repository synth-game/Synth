#include "ChangeStateEvent.h"

namespace events {

const char* ChangeStateEvent::EVENT_NAME = "ChangeStateEvent";

ChangeStateEvent::ChangeStateEvent(Node* pSource, graphics::ActorState eState)
	: SynthEvent(pSource, ChangeStateEvent::EVENT_NAME)
	, _eNewState(eState) {
}

ChangeStateEvent::~ChangeStateEvent() {
}

}  // namespace events