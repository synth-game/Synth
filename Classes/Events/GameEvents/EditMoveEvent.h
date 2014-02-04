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

	boolean _bChangeX;

	boolean _bChangeY;

public:
	static char* sEventName;


public:
	EditMoveEvent();

	/**
	 *  
	 */
	~EditMoveEvent();

	Events::Point getDirection();

	boolean getChangeX();

	boolean getChangeY();

	void setDirection(Events::Point direction);

	void setChangeX(boolean changeX);

	void setChangeY(boolean changeY);

};

}  // namespace GameEvents
}  // namespace Events
#endif
