#include "ChangePositionEvent.h"

namespace events
{

const char* ChangePositionEvent::EVENT_NAME = "ChangePositionEvent";

ChangePositionEvent::ChangePositionEvent()
{
}

ChangePositionEvent::~ChangePositionEvent()
{
}

Point ChangePositionEvent::getCurrentPosition()
{
	return Point::ZERO;
}

void ChangePositionEvent::setCurrentPosition(Point position)
{
}

}  // namespace events
