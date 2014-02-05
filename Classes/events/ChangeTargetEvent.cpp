#include "ChangeTargetEvent.h"

namespace events
{
namespace GameEvents
{
char* ChangeTargetevent::sEventName;

ChangeTargetevent::ChangeTargetEvent()
{
}

ChangeTargetevent::~ChangeTargetEvent()
{
}

events::Point ChangeTargetevent::getNewTarget()
{
	return 0;
}

void ChangeTargetevent::setNewTarget(events::Point newTarget)
{
}
}  // namespace GameEvents
}  // namespace events
