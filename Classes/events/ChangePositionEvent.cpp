#include "ChangePositionEvent.h"

namespace events
{
namespace GameEvents
{
char* ChangePositionevent::sEventName;

ChangePositionevent::ChangePositionEvent()
{
}

ChangePositionevent::~ChangePositionEvent()
{
}

events::Point ChangePositionevent::getCurrentPosition()
{
	return 0;
}

void ChangePositionevent::setCurrentPosition(events::Point position)
{
}
}  // namespace GameEvents
}  // namespace events
