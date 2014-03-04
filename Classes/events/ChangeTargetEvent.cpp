/*!
 * \file ChangeTargetEvent.cpp
 * \brief Change the target of the follow movement
 * \author Chupee
 * \date 04/03/2014
 */
#include "ChangeTargetEvent.h"

namespace events {

const char* ChangeTargetEvent::EVENT_NAME = "ChangeTargetEvent";

ChangeTargetEvent::ChangeTargetEvent(Node* pSource, Point newTarget) :
	SynthEvent(pSource, EVENT_NAME),
	_newTarget(newTarget) {
}

ChangeTargetEvent::~ChangeTargetEvent() {
}


}  // namespace events
