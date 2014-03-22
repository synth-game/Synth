/*!
 * \file JumpEvent.cpp
 * 
 * \author Flora Jullien
 * \date 19/02/2014
 */
#include "JumpEvent.h"

namespace events {

const char* JumpEvent::EVENT_NAME = "jump_event";

JumpEvent::JumpEvent(Node* pSource , bool bStartJump)
    : SynthEvent(pSource, EVENT_NAME), _bStartJump(bStartJump), _direction(Point(0,1)) {
}

JumpEvent::JumpEvent(Node* pSource, Point direction, bool bStartJump)
    : SynthEvent(pSource, EVENT_NAME), _bStartJump(bStartJump), _direction(direction) {
}


JumpEvent::~JumpEvent() {

}

}  // namespace events
