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

Events::Point TestCollisionevent::getCurrentPosition()
{
	return 0;
}

Events::Point TestCollisionevent::getTargetPosition()
{
	return 0;
}

Events::Size TestCollisionevent::getSize()
{
	return 0;
}

void TestCollisionevent::setCurrentPosition(Events::Point position)
{
}

void TestCollisionevent::setTargetPosition(Events::Point position)
{
}

void TestCollisionevent::setSize(Events::Size size)
{
}
}  // namespace GameEvents
}  // namespace events
