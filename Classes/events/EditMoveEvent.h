#ifndef EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H
#define EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events
{
class EditMoveEvent : public events::SynthEvent
{
private:
	Point _direction;

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

	Point getDirection();

	bool getChangeX();

	bool getChangeY();

	void setDirection(Point direction);

	void setChangeX(bool changeX);

	void setChangeY(bool changeY);

};

}  // namespace events
#endif
