/*!
 * \file EditMoveEvent.cpp
 * 
 * \author Flora Jullien
 * \date 12/02/2014
 */
#include "EditMoveEvent.h"

namespace events {

const char* EditMoveEvent::EVENT_NAME = "edit_move_event";

EditMoveEvent::EditMoveEvent(Node* pSource, Point direction, bool changeX, bool changeY, bool startMoving) 
	: SynthEvent(pSource, EVENT_NAME), _direction(direction), _bChangeX(changeX), _bChangeY(changeY), _bStartMoving(startMoving){
}

EditMoveEvent::~EditMoveEvent() {

}

}  // namespace events
