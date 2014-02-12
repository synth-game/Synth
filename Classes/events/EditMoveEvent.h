/*!
 * \file EditMoveEvent.h
 * 
 * \author Flora Jullien
 * \date 12/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H
#define EVENTS_GAMEEVENTS_EDIT_MOVE_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {

/*! \class EditMoveEvent */
class EditMoveEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	EditMoveEvent();
	/*! \brief Destructor */
	~EditMoveEvent();

	inline Point getDirection() { return _direction; }
	inline bool getChangeX() { return _bChangeX; }
	inline bool getChangeY() { return _bChangeY; }
	inline bool isStartMoving() { return _bStartMoving; }
	inline void setDirection(Point direction) { _direction = direction; } 
	inline void setChangeX(bool changeX) { _bChangeX = changeX; }
	inline void setChangeY(bool changeY) { _bChangeY = changeY; }
	inline void setStartMoving(bool start) { _bStartMoving = start; }

	static char* sEventName;

private:
	Point _direction;
	bool _bChangeX;
	bool _bChangeY;
	bool _bStartMoving;
};

}  // namespace events
#endif
