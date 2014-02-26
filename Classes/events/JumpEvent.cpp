/*!
 * \file JumpEvent.cpp
 * 
 * \author Flora Jullien
 * \date 19/02/2014
 */
#include "JumpEvent.h"

namespace events {

const char* JumpEvent::EVENT_NAME = "jump_event";

JumpEvent::JumpEvent(Node* pSource, bool bStartJump)
    : SynthEvent(pSource, EVENT_NAME), _bStartJump(bStartJump) {
}

JumpEvent::~JumpEvent() {

}

}  // namespace events
