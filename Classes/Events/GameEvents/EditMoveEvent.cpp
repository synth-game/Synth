#include "EditMoveEvent.h"

namespace Events
{
namespace GameEvents
{
char* EditMoveEvent::sEventName;

EditMoveEvent::EditMoveEvent()
{
}

EditMoveEvent::~EditMoveEvent()
{
}

Events::Point EditMoveEvent::getDirection()
{
	return 0;
}

boolean EditMoveEvent::getChangeX()
{
	return 0;
}

boolean EditMoveEvent::getChangeY()
{
	return 0;
}

void EditMoveEvent::setDirection(Events::Point direction)
{
}

void EditMoveEvent::setChangeX(boolean changeX)
{
}

void EditMoveEvent::setChangeY(boolean changeY)
{
}
}  // namespace GameEvents
}  // namespace Events
