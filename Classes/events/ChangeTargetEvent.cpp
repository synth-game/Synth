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

Events::Point ChangeTargetevent::getNewTarget()
{
	return 0;
}

void ChangeTargetevent::setNewTarget(Events::Point newTarget)
{
}
}  // namespace GameEvents
}  // namespace events
