#ifndef EVENTS_GAMEEVENTS_CHANGE_INTENSITY_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_INTENSITY_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {

class ChangeIntensityEvent : public events::SynthEvent {
private:

public:
	static const char* EVENT_NAME;


public:
	ChangeIntensityEvent();

	~ChangeIntensityEvent();

};

}  // namespace events
#endif
