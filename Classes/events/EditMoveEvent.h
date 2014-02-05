#ifndef EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H
#define EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H

#include "Events/SynthEvent.h"
#include "Events/Point.h"

namespace events
{
namespace GameEvents
{
class EditMoveEvent : public events::SynthEvent
{
private:
	events::Point _direction;

	bool _bChangeX;

	bool _bChangeY;

public:
	static char* sEventName;


public:
	EditMoveEvent();

	/**
	 *
	 */
	~EditMoveEvent();

	events::Point getDirection();

	bool getChangeX();

	bool getChangeY();

	void setDirection(events::Point direction);

	void setChangeX(bool changeX);

	void setChangeY(bool changeY);

};

}  // namespace GameEvents
}  // namespace events
#endif
