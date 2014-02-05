#include "TestCollisionEvent.h"

namespace events
{
namespace GameEvents
{
char* TestCollisionevent::sEventName;

TestCollisionevent::TestCollisionEvent()
{
}

TestCollisionevent::~TestCollisionEvent()
{
}

events::Point TestCollisionevent::getCurrentPosition()
{
	return 0;
}

events::Point TestCollisionevent::getTargetPosition()
{
	return 0;
}

events::Size TestCollisionevent::getSize()
{
	return 0;
}

void TestCollisionevent::setCurrentPosition(events::Point position)
{
}

void TestCollisionevent::setTargetPosition(events::Point position)
{
}

void TestCollisionevent::setSize(events::Size size)
{
}
}  // namespace GameEvents
}  // namespace events
