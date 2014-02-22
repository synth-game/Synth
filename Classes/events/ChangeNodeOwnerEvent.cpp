#include "ChangeNodeOwnerEvent.h"

namespace events {

const char* ChangeNodeOwnerEvent::EVENT_NAME = "ChangeNodeOwnerEvent";

ChangeNodeOwnerEvent::ChangeNodeOwnerEvent() {
}

ChangeNodeOwnerEvent::~ChangeNodeOwnerEvent() {
}

Node* ChangeNodeOwnerEvent::_getNewOwner() {
	return nullptr;
}

}  // namespace events
