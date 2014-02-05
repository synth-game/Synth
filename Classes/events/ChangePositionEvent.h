#ifndef EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H

#include "Events/SynthEvent.h"
#include "Events/Point.h"

namespace events
{
namespace GameEvents
{
class ChangePositionEvent : public events::SynthEvent
{
private:
	events::Point _currentPosition;

public:
	static char* sEventName;


public:
	ChangePositionEvent();

	/**
	 *
	 */
	~ChangePositionEvent();

	events::Point getCurrentPosition();

	void setCurrentPosition(events::Point position);

};

}  // namespace GameEvents
}  // namespace events
#endif
