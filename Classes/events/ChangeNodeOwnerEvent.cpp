/*!
 * \file ChangeNodeOwnerEvent.cpp
 * \brief Event that announce that an actor changes its owner.
 * \author Chupee
 * \date 26/02/2014
 */
#include "ChangeNodeOwnerEvent.h"

namespace events {

const char* ChangeNodeOwnerEvent::EVENT_NAME = "ChangeNodeOwnerEvent";

ChangeNodeOwnerEvent::ChangeNodeOwnerEvent(Node* owned, Node* newOwner) :
    SynthEvent(owned, EVENT_NAME),
	_owned(owned),
	_newOwner(newOwner) {
}

ChangeNodeOwnerEvent::~ChangeNodeOwnerEvent() {
}

}  // namespace events
