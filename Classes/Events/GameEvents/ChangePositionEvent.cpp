#include "ChangePositionEvent.h"

namespace Events
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

Events::Point ChangePositionEvent::getCurrentPosition()
{
	return 0;
}

void ChangePositionEvent::setCurrentPosition(Events::Point position)
{
}
}  // namespace GameEvents
}  // namespace Events
