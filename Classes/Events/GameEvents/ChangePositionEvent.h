#ifndef EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H

#include "Events/SynthEvent.h"
#include "Events/Point.h"

namespace events
{
namespace GameEvents
{
class ChangePositionEvent : public Events::SynthEvent
{
private:
	Events::Point _currentPosition;

public:
	static char* sEventName;


public:
	ChangePositionEvent();

	/**
	 *
	 */
	~ChangePositionEvent();

	Events::Point getCurrentPosition();

	void setCurrentPosition(Events::Point position);

};

}  // namespace GameEvents
}  // namespace events
#endif
