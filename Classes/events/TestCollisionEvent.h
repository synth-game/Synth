/*!
 * \file TestCollisionEvent.h
 * \brief Main manager, the entry point of our program
 * \author Flora Jullien
 * \date 12/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H
#define EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {

/*! \class TestCollisionEvent */
class TestCollisionEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	TestCollisionEvent();
	/*! \brief Destructor */
	~TestCollisionEvent();

	inline Point getCurrentPosition() { return _currentPosition; }
	inline Point getTargetPosition() { return _targetPosition; }
	inline Size getSize() { return _size; }
	inline void setCurrentPosition(Point position) { _currentPosition = position; }
	inline void setTargetPosition(Point position) { _targetPosition = position; }
	inline void setSize(Size size) { _size = size; }

	static char* sEventName;

private:
	Point _currentPosition;
	Point _targetPosition;
	Size _size;
};

}  // namespace events
#endif
