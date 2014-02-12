/*!
 * \file ChangePositionEvent.h
 * \brief Main manager, the entry point of our program
 * \author Flora Jullien
 * \date 12/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_POSITION_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {

/*! \class ChangePositionEvent */
class ChangePositionEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	ChangePositionEvent();
	/*! \brief Destructor */
	~ChangePositionEvent();

	inline Point getCurrentPosition() { return _currentPosition; }
	inline void setCurrentPosition(Point position) { _currentPosition = position; }

	static const char* EVENT_NAME;

private:
	Point _currentPosition;
};

}  // namespace events
#endif
