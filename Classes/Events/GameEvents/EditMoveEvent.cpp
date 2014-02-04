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

bool EditMoveEvent::getChangeX()
{
	return 0;
}

bool EditMoveEvent::getChangeY()
{
	return 0;
}

void EditMoveEvent::setDirection(Events::Point direction)
{
}

void EditMoveEvent::setChangeX(bool changeX)
{
}

void EditMoveEvent::setChangeY(bool changeY)
{
}
}  // namespace GameEvents
}  // namespace Events
