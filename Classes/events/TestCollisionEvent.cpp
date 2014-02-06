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

void TestCollisionEvent::setTargetPosition(Point position)
{
}

void TestCollisionEvent::setSize(Size size)
{
}
}  // namespace GameEvents
}  // namespace events
