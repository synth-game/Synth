#ifndef EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events
{

class ChangePositionEvent : public events::SynthEvent
{
private:
	Point _currentPosition;

public:
	static char* EVENT_NAME;


public:
	ChangePositionEvent();

	/**
	 *
	 */
	~ChangePositionEvent();

	Point getCurrentPosition();

	void setCurrentPosition(Point position);

};

}  // namespace events
#endif
