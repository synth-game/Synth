#ifndef EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H
#define EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H

#include "Events/SynthEvent.h"
#include "Events/Point.h"
#include "Events/Size.h"

namespace events
{
namespace GameEvents
{
class TestCollisionEvent : public events::SynthEvent
{
private:
	events::Point _currentPosition;

	events::Point _targetPosition;

	events::Size _size;

public:
	static char* sEventName;


public:
	TestCollisionEvent();

	/**
	 *
	 */
	~TestCollisionEvent();

	events::Point getCurrentPosition();

	events::Point getTargetPosition();

	events::Size getSize();

	void setCurrentPosition(events::Point position);

	void setTargetPosition(events::Point position);

	void setSize(events::Size size);

};

}  // namespace GameEvents
}  // namespace events
#endif
