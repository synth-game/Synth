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

Events::Point ChangePositionevent::getCurrentPosition()
{
	return 0;
}

void ChangePositionevent::setCurrentPosition(Events::Point position)
{
}
}  // namespace GameEvents
}  // namespace events
