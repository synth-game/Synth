/*!
 * \file ChangeNodeOwnerEvent.cpp
 * \brief Event that announce that an actor changes its owner.
 * \author Chupee
 * \date 26/02/2014
 */
#include "ChangeNodeOwnerEvent.h"

namespace events {

const char* ChangeNodeOwnerEvent::EVENT_NAME = "ChangeNodeOwnerEvent";

ChangeNodeOwnerEvent::ChangeNodeOwnerEvent(Node* manager, Node* owned, Node* newOwner, Node* previousOwner) :
    SynthEvent(manager, EVENT_NAME),
	_owned(owned),
	_newOwner(newOwner),
	_previousOwner(previousOwner) {
}

ChangeNodeOwnerEvent::~ChangeNodeOwnerEvent() {
}

}  // namespace events
