#include "EditMoveEvent.h"

namespace events
{
namespace GameEvents
{
char* EditMoveevent::sEventName;

EditMoveevent::EditMoveEvent()
{
}

EditMoveevent::~EditMoveEvent()
{
}

Events::Point EditMoveevent::getDirection()
{
	return 0;
}

bool EditMoveevent::getChangeX()
{
	return 0;
}

bool EditMoveevent::getChangeY()
{
	return 0;
}

void EditMoveevent::setDirection(Events::Point direction)
{
}

void EditMoveevent::setChangeX(bool changeX)
{
}

void EditMoveevent::setChangeY(bool changeY)
{
}
}  // namespace GameEvents
}  // namespace events
