#include "TestCollisionEvent.h"

namespace Events
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

Events::Point TestCollisionEvent::getCurrentPosition()
{
	return 0;
}

Events::Point TestCollisionEvent::getTargetPosition()
{
	return 0;
}

Events::Size TestCollisionEvent::getSize()
{
	return 0;
}

void TestCollisionEvent::setCurrentPosition(Events::Point position)
{
}

void TestCollisionEvent::setTargetPosition(Events::Point position)
{
}

void TestCollisionEvent::setSize(Events::Size size)
{
}
}  // namespace GameEvents
}  // namespace Events
