/* *****************************************************
 * SynthEvent.h - @ Flora Jullien - 4/02/14
 ***************************************************** */

#include "events/SynthEvent.h"

SynthEvent::SynthEvent(Node* source, const char* eventName) 
	: EventCustom(eventName) {
	_source = source;
}

SynthEvent::~SynthEvent() {

}