#ifndef EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H
#define EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H

#include "Events/SynthEvent.h"
#include "Events/Point.h"

namespace Events
{
namespace GameEvents
{
class EditMoveEvent : public Events::SynthEvent
{
private:
	Events::Point _direction;

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

	Events::Point getDirection();

	bool getChangeX();

	bool getChangeY();

	void setDirection(Events::Point direction);

	void setChangeX(bool changeX);

	void setChangeY(bool changeY);

};

}  // namespace GameEvents
}  // namespace Events
#endif
