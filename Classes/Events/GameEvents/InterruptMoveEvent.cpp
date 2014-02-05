#include "InterruptMoveEvent.h"

namespace events
{
namespace GameEvents
{
char* InterruptMoveevent::sEventName;

InterruptMoveevent::InterruptMoveEvent()
{
}

InterruptMoveevent::~InterruptMoveEvent()
{
}

bool InterruptMoveevent::getStopX()
{
	return 0;
}

bool InterruptMoveevent::getStopY()
{
	return 0;
}

bool InterruptMoveevent::getHasMoved()
{
	return 0;
}

void InterruptMoveevent::setStopX(bool stopX)
{
}

void InterruptMoveevent::setStopY(bool stopY)
{
}

bool InterruptMoveevent::setHasMoved()
{
	return 0;
}
}  // namespace GameEvents
}  // namespace events
