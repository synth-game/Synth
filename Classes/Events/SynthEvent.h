#ifndef EVENTS_SYNTH_EVENT_H
#define EVENTS_SYNTH_EVENT_H

#include "cocos2d.h"

USING_NS_CC;

namespace events
{
class SynthEvent : public EventCustom
{
protected:
	Node* _pSource;


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
