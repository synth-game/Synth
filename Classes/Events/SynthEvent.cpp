/*!
 * \file SynthEvent.cpp
 * \brief Base classe of out events
 * \author Jijidici
 * \date 09/02/2014
 */
#include "SynthEvent.h"

namespace events {

SynthEvent::SynthEvent()
	: EventCustom("") 
	, _pSource(nullptr) {

}

SynthEvent::SynthEvent(Node* pSource, const char* pEventName)
	: EventCustom(pEventName) 
	, _pSource(pSource) {

}

SynthEvent::~SynthEvent() {

}

}  // namespace Events
