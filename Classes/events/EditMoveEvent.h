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

	bool _bStart;

public:
	static const char* EVENT_NAME;


public:
	EditMoveEvent();

	/**
	 *
	 */
	~EditMoveEvent();

	Point getDirection();

	bool getChangeX();

	bool getChangeY();

	bool getStart();

	void setDirection(Point direction);

	void setChangeX(bool bChangeX);

	void setChangeY(bool bChangeY);

	void setStart(bool bStart);

};

}  // namespace events
#endif
