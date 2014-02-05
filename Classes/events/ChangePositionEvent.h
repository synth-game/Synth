#ifndef EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events
{
namespace GameEvents
{
class ChangePositionEvent : public events::SynthEvent
{
private:
	Point _currentPosition;

public:
	static char* sEventName;


public:
	ChangePositionEvent();

	/**
	 *
	 */
	~ChangePositionEvent();

	Point getCurrentPosition();

	void setCurrentPosition(Point position);

};

}  // namespace GameEvents
}  // namespace events
#endif
