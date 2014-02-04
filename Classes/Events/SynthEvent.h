#ifndef EVENTS_SYNTH_EVENT_H
#define EVENTS_SYNTH_EVENT_H

#include "Node.h"
#include "Events/EventCustom.h"
#include "Events/GameEvents/ChangeTargetEvent.h"

namespace Events
{
class SynthEvent : public EventCustom, public GameEvents::ChangeTargetEvent
{
protected:
	Node* _source;


public:
	SynthEvent();

	/**
	 *  
	 */
	~SynthEvent();

	Node* getSource();

};

}  // namespace Events
#endif
