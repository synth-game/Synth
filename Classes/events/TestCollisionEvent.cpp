#include "TestCollisionEvent.h"

namespace events
{
namespace GameEvents
{
char* TestCollisionEvent::sEventName;

TestCollisionEvent::TestCollisionEvent()
{
}

TestCollisionEvent::~TestCollisionEvent()
{
}

Point TestCollisionEvent::getCurrentPosition()
{
	return Point::ZERO;
}

Point TestCollisionEvent::getTargetPosition()
{
	return Point::ZERO;
}

Size TestCollisionEvent::getSize()
{
	return Size::ZERO;
}

void TestCollisionEvent::setCurrentPosition(Point position)
{
}

void TestCollisionevent::setTargetPosition(Point position)
{
}

void TestCollisionevent::setSize(Size size)
{
}
}  // namespace GameEvents
}  // namespace events
