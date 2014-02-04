#ifndef EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H
#define EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H

#include "Events/SynthEvent.h"
#include "Events/Point.h"
#include "Events/Size.h"

namespace Events
{
namespace GameEvents
{
class TestCollisionEvent : public Events::SynthEvent
{
private:
	Events::Point _currentPosition;

	Events::Point _targetPosition;

	Events::Size _size;

public:
	static char* sEventName;


public:
	TestCollisionEvent();

	/**
	 *  
	 */
	~TestCollisionEvent();

	Events::Point getCurrentPosition();

	Events::Point getTargetPosition();

	Events::Size getSize();

	void setCurrentPosition(Events::Point position);

	void setTargetPosition(Events::Point position);

	void setSize(Events::Size size);

};

}  // namespace GameEvents
}  // namespace Events
#endif
