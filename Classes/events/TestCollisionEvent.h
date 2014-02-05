#ifndef EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H
#define EVENTS_GAMEEVENTS_TEST_COLLISION_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events
{
namespace GameEvents
{
class TestCollisionEvent : public events::SynthEvent
{
private:
	Point _currentPosition;

	Point _targetPosition;

	Size _size;

public:
	static char* sEventName;


public:
	TestCollisionEvent();

	/**
	 *
	 */
	~TestCollisionEvent();

	Point getCurrentPosition();

	Point getTargetPosition();

	Size getSize();

	void setCurrentPosition(Point position);

	void setTargetPosition(Point position);

	void setSize(Size size);

};

}  // namespace GameEvents
}  // namespace events
#endif
