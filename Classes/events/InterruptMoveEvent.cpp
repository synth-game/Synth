/*!
 * \file InterruptMoveEvent.cpp
 * 
 * \author Flora Jullien
 * \date 19/02/2014
 */
#include "InterruptMoveEvent.h"

namespace events {

const char* InterruptMoveEvent::EVENT_NAME = "interrupt_move_event";

InterruptMoveEvent::InterruptMoveEvent(Node* pSource, bool bStopX, bool bStopY, bool bHasMoved)
    : SynthEvent(pSource, EVENT_NAME), _bStopX(bStopX), _bStopY(bStopY), _bHasMoved(bHasMoved){

}

InterruptMoveEvent::~InterruptMoveEvent() {

}

}  // namespace events
