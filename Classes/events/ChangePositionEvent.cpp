#include "ChangePositionEvent.h"

namespace events
{
namespace GameEvents
{
char* ChangePositionEvent::sEventName;

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
}  // namespace GameEvents
}  // namespace events
