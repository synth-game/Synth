/*!
 * \file ChangePositionEvent.cpp
 * \brief Main manager, the entry point of our program
 * \author Flora Jullien
 * \date 12/02/2014
 */
#include "ChangePositionEvent.h"

namespace events {

const char* ChangePositionEvent::EVENT_NAME = "ChangePositionEvent";

ChangePositionEvent::ChangePositionEvent(Node* pSource, Point position)
	: SynthEvent(pSource, ChangePositionEvent::EVENT_NAME), _currentPosition(position) {

}

ChangePositionEvent::~ChangePositionEvent() {

}

}  // namespace events
