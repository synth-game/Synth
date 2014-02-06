#include "SynthEvent.h"

namespace events
{

SynthEvent::SynthEvent()
	: EventCustom("") 
	, _pSource(nullptr) {
}

SynthEvent::~SynthEvent()
{
}

Node* SynthEvent::getSource()
{
	return nullptr;
}
}  // namespace Events
