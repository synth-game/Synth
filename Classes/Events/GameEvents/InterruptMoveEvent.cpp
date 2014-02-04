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

boolean InterruptMoveEvent::getStopX()
{
	return 0;
}

boolean InterruptMoveEvent::getStopY()
{
	return 0;
}

boolean InterruptMoveEvent::getHasMoved()
{
	return 0;
}

void InterruptMoveEvent::setStopX(boolean stopX)
{
}

void InterruptMoveEvent::setStopY(boolean stopY)
{
}

boolean InterruptMoveEvent::setHasMoved()
{
	return 0;
}
}  // namespace GameEvents
}  // namespace Events
