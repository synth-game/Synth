#include "EditMoveEvent.h"

namespace events
{

const char* EditMoveEvent::EVENT_NAME = "EditMoveEvent";

EditMoveEvent::EditMoveEvent()
{
}

EditMoveEvent::~EditMoveEvent()
{
}

Point EditMoveEvent::getDirection()
{
	return Point::ZERO;
}

bool EditMoveEvent::getChangeX()
{
	return 0;
}

bool EditMoveEvent::getChangeY()
{
	return 0;
}

void EditMoveEvent::setDirection(Point direction)
{
}

void EditMoveEvent::setChangeX(bool changeX)
{
}

void EditMoveEvent::setChangeY(bool changeY)
{
}
}  // namespace events
