#include "ChangeTargetEvent.h"

namespace events
{
namespace GameEvents
{
char* ChangeTargetEvent::sEventName;

ChangeTargetEvent::ChangeTargetEvent()
{
}

ChangeTargetEvent::~ChangeTargetEvent()
{
}

Point ChangeTargetEvent::getNewTarget()
{
	return Point::ZERO;
}

void ChangeTargetEvent::setNewTarget(Point newTarget)
{
}
}  // namespace GameEvents
}  // namespace events
