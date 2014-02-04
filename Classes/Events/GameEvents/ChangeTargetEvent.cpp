#include "ChangeTargetEvent.h"

namespace Events
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

Events::Point ChangeTargetEvent::getNewTarget()
{
	return 0;
}

void ChangeTargetEvent::setNewTarget(Events::Point newTarget)
{
}
}  // namespace GameEvents
}  // namespace Events
