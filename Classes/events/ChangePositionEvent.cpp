/* *****************************************************
 * ChangePositionEvent.h - @ Flora Jullien - 4/02/14
 ***************************************************** */

#include "events/ChangePositionEvent.h"

const char* ChangePositionEvent::EVENT_NAME = "ChangePositionEvent";

ChangePositionEvent::ChangePositionEvent(Node* source) 
	: SynthEvent(source, ChangePositionEvent::EVENT_NAME) {

}

ChangePositionEvent::~ChangePositionEvent() {

}
