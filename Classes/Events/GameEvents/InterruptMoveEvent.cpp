#include "InterruptMoveEvent.h"

namespace Events
{
namespace GameEvents
{
char* InterruptMoveEvent::sEventName;

InterruptMoveEvent::InterruptMoveEvent()
{
}

InterruptMoveEvent::~InterruptMoveEvent()
{
}

bool InterruptMoveEvent::getStopX()
{
	return 0;
}

bool InterruptMoveEvent::getStopY()
{
	return 0;
}

bool InterruptMoveEvent::getHasMoved()
{
	return 0;
}

void InterruptMoveEvent::setStopX(bool stopX)
{
}

void InterruptMoveEvent::setStopY(bool stopY)
{
}

bool InterruptMoveEvent::setHasMoved()
{
	return 0;
}
}  // namespace GameEvents
}  // namespace Events
